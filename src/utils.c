#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include "cbpro.h"

struct Digest {
    char message[300];
    char sig[45];
};

struct Request {
    char method[10];
    char requestPath[200];
    char url[200];
    char timestamp[11];
    struct Digest *digest;
};

/*
 * Constructs the message sent to the coinbase API:
 *   The Secret Key is first base64 decoded.
 *   The result is used to sign the HMAC which uses a sha256 digest.
 *   This output is then base64 encoded.
*/
void create_signature(struct Digest *digest, struct Client *client);
void create_message(struct Request *request);
struct Request *init_request(const char *requestPath, char *method);
struct Request *init_cb_request(const char *requestPath, char *method);

CURL *init_session();
struct curl_slist *set_headers(struct Request *request, struct Client *client);
size_t write_cb(char *contents, size_t itemsize, size_t nitems, void *stream);

struct DataBuf *data_buffer_create();
int data_buffer_reset(struct DataBuf *data_buf);

CURL *init_session() {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Libcurl/3.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

    return curl;
}

struct Client *client_create() {
    struct Client *client = malloc(sizeof(struct Client));
    client->data = data_buffer_create();
    client->session = init_session();
    client->authenticated = false;
    return client;
}

int authorize_client(FILE *fh, struct Client *client) {
    const size_t MAX_LEN = 100;
    const size_t MAX_CMP = 11;

    if (!fh) {
        return(FILE_NOT_FOUND);
    }

    client->creds = malloc(sizeof(struct Credentials));
    if (client->creds == NULL) {
        return(FAILED_MEMORY_ALLOCATION);
    }

    char line[256];
    while (fgets(line, sizeof(line), fh)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, " ");

        if (!strncmp(token, "secret_key", MAX_CMP)) {
            token = strtok(NULL, " ");
            client->creds->secret_key = malloc(strnlen(token, MAX_LEN)+1);
            if (client->creds->secret_key == NULL) {
                return(FAILED_MEMORY_ALLOCATION);
            }
            strncpy(client->creds->secret_key, token, strnlen(token, MAX_LEN)+1);
        } else if (!strncmp(token, "api_key", MAX_CMP)) {
            token = strtok(NULL, " ");
            client->creds->api_key = malloc(strnlen(token, MAX_LEN)+1);
            if (client->creds->api_key == NULL) {
                return(FAILED_MEMORY_ALLOCATION);
            }
            strncpy(client->creds->api_key, token, strnlen(token, MAX_LEN)+1);
        } else if (!strncmp(token, "passphrase", MAX_CMP)) {
            token = strtok(NULL, " ");
            client->creds->passphrase = malloc(strnlen(token, MAX_LEN)+1);
            if (client->creds->passphrase == NULL) {
                return(FAILED_MEMORY_ALLOCATION);
            }
            strncpy(client->creds->passphrase, token, strnlen(token, MAX_LEN)+1);
        }
    }
    client->authenticated = true;

    fclose(fh);
    return(0);
}

void client_cleanup(struct Client *client) {
    if(client->authenticated == true) {
        free(client->creds->passphrase);
        free(client->creds->api_key);
        free(client->creds->secret_key);
        free(client->creds);
        client->authenticated = false;
    }

    if(client->data->size > 0) {
        free(client->data->buffer);
    }

    free(client->data);
    curl_easy_cleanup(client->session);
    curl_global_cleanup();
    free(client);
}

struct Request *init_request(const char *requestPath, char *method) {
    struct Request *request = (struct Request *)malloc(sizeof(struct Request));
    if (!request) {
        printf("Unable to allocate memory for request.\n");
        exit(1);
    }

    request->digest = (struct Digest *)malloc(sizeof(struct Digest));
    if (!request->digest) {
        printf("Unable to allocate memory for digest.\n");
        exit(1);
    }

    char url[200] = "https://api.exchange.coinbase.com";
    strcat(url, requestPath);

    strcpy(request->url, url);
    strcpy(request->method, method);
    strcpy(request->requestPath, requestPath);

    return request;
}

struct Request *init_cb_request(const char *requestPath, char *method) {
    struct Request *request = (struct Request *)malloc(sizeof(struct Request));
    if (!request) {
        printf("Unable to allocate memory for request.\n");
        exit(1);
    }

    request->digest = (struct Digest *)malloc(sizeof(struct Digest));
    if (!request->digest) {
        printf("Unable to allocate memory for digest.\n");
        exit(1);
    }
    char url[200] = "https://api.coinbase.com/v2";
    strcat(url, requestPath);

    strcpy(request->url, url);
    strcpy(request->method, method);
    strcpy(request->requestPath, requestPath);

    return request;
}

struct DataBuf *data_buffer_create() {
    struct DataBuf *data_buffer = (struct DataBuf *)malloc(sizeof(struct DataBuf));
    if (!data_buffer) {
        printf("Unable to allocate memory for json buffer");
        exit(1);
    }

    data_buffer->buffer = malloc(1);
    if (!data_buffer->buffer) {
        printf("Unable to allocate memory for json buffer.\n");
        exit(1);
    }
    data_buffer->size = 0;

    return data_buffer;
}

int data_buffer_reset(struct DataBuf *data_buf) {
    if(data_buf->size > 0) {
        free(data_buf->buffer);

        data_buf->buffer = malloc(1);
        if (data_buf->buffer == NULL) {
            return(FAILED_MEMORY_ALLOCATION);
        }

        data_buf->size = 0;
    }
    return(0);
}

void create_message(struct Request *request) {
    const size_t MAX_LEN = 100;

    time_t time_now = time(NULL);
    sprintf(request->timestamp, "%ld", time_now);

    strncpy(request->digest->message, request->timestamp, MAX_LEN);
    strncat(request->digest->message, request->method, MAX_LEN);
    strncat(request->digest->message, request->requestPath, MAX_LEN);
}

void create_signature(struct Digest *digest, struct Client *client) {
    char hmac_key[65];
    int key_len = 64;

    EVP_DecodeBlock((unsigned char *)hmac_key,
                     (const unsigned char *)client->creds->secret_key,
                     strlen(client->creds->secret_key));

    unsigned char *hmac = NULL;
    unsigned int hmac_len;
    hmac = HMAC(EVP_sha256(),
                (const void *)hmac_key,
                key_len,
                (const unsigned char*)digest->message,
                strlen(digest->message),
                hmac,
                &hmac_len);

    EVP_EncodeBlock((unsigned char *)digest->sig,
                    (const unsigned char *)hmac,
                    hmac_len);
}

struct curl_slist *set_headers(struct Request *request, struct Client *client) {
    create_message(request);
    create_signature(request->digest, client);

    char cb_timestamp_header[100] = "cb-access-timestamp: ";
    strncat(cb_timestamp_header, request->timestamp, 100);

    char cb_access_header[100] = "cb-access-sign: ";
    strncat(cb_access_header, request->digest->sig, 100);

    char api_key_header[100] = "cb-access-key: ";
    strncat(api_key_header, client->creds->api_key, 100);

    char passphrase_header[100] = "cb-access-passphrase: ";
    strncat(passphrase_header, client->creds->passphrase, 100);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, api_key_header);
    headers = curl_slist_append(headers, passphrase_header);
    headers = curl_slist_append(headers, cb_access_header);
    headers = curl_slist_append(headers, cb_timestamp_header);

    return headers;
}

void send_unauth_request(struct Client *client, const char *requestPath, enum Method req_method) {
    data_buffer_reset(client->data);
    char method[7];
    switch(req_method) {
        case GET:
            strncpy(method, "GET", 4);
            break;
        case POST:
            strncpy(method, "POST", 5);
            break;
        case PUT:
            strncpy(method, "PUT", 4);
            break;
        case DELETE:
            strncpy(method, "DELETE", 7);
            break;
        default:
            strncpy(method, "ERR", 4);
            break;
    }

    struct Request *request = init_request(requestPath, method);
    curl_easy_setopt(client->session, CURLOPT_URL, request->url);
    curl_easy_setopt(client->session, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(client->session, CURLOPT_WRITEDATA, (void *)client->data);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(client->session, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(client->session);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    free(request->digest);
    free(request);
}

void send_cb_unauth_request(struct Client *client, const char *requestPath, enum Method req_method) {
    data_buffer_reset(client->data);
    char method[7];
    switch(req_method) {
        case GET:
            strncpy(method, "GET", 4);
            break;
        case POST:
            strncpy(method, "POST", 5);
            break;
        case PUT:
            strncpy(method, "PUT", 4);
            break;
        case DELETE:
            strncpy(method, "DELETE", 7);
            break;
        default:
            strncpy(method, "ERR", 4);
            break;
    }

    struct Request *request = init_cb_request(requestPath, method);
    curl_easy_setopt(client->session, CURLOPT_URL, request->url);
    curl_easy_setopt(client->session, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(client->session, CURLOPT_WRITEDATA, (void *)client->data);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(client->session, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(client->session);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    free(request->digest);
    free(request);
}

void send_request(struct Client *client, const char *requestPath, enum Method req_method) {
    data_buffer_reset(client->data);

    char method[7];
    switch(req_method) {
        case GET:
            strncpy(method, "GET", 4);
            break;
        case POST:
            strncpy(method, "POST", 5);
            break;
        case PUT:
            strncpy(method, "PUT", 4);
            break;
        case DELETE:
            strncpy(method, "DELETE", 7);
            break;
        default:
            strncpy(method, "ERR", 4);
            break;
    }

    struct Request *request = init_request(requestPath, method);
    curl_easy_setopt(client->session, CURLOPT_URL, request->url);
    curl_easy_setopt(client->session, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(client->session, CURLOPT_WRITEDATA, (void *)client->data);

    struct curl_slist *headers = set_headers(request, client);
    curl_easy_setopt(client->session, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(client->session);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    free(request->digest);
    free(request);
}

size_t write_cb(char *contents, size_t itemsize, size_t nitems, void *stream) {
    size_t bytes = itemsize * nitems;
    struct DataBuf *buf = (struct DataBuf *)stream;

    char *ptr = realloc(buf->buffer, buf->size + bytes + 1);
    if (!ptr) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    buf->buffer = ptr;
    memcpy(&(buf->buffer[buf->size]), contents, bytes);
    buf->size += bytes;
    buf->buffer[buf->size] = 0;

    return bytes;
}
