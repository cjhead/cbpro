#include "utils.h"
#include "cbpro.h"

CURL *init_session() {

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Libcurl/3.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

    return curl;
}

struct AuthClient *create_auth_client(const char *filename) {

    const size_t MAX_LEN = 100;
    const size_t MAX_CMP = 11;

    struct AuthClient *auth_client = (struct AuthClient *)malloc(sizeof(struct AuthClient));
    if (auth_client == NULL) {
        printf("Unable to allocate memory for auth_client.\n");
        exit(1);
    }

    FILE *fh = fopen(filename, "r");
    if (!fh) {
        printf("File with credentials not found\n");
    exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fh)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, " ");

        if (!strncmp(token, "secret_key", MAX_CMP)) {
            token = strtok(NULL, " ");
            auth_client->secret_key = malloc(strnlen(token, MAX_LEN)+1);
            if (auth_client->secret_key == NULL) {
                printf("Unable to allocate memory for secret key.\n");
                exit(1);
            }
            strncpy(auth_client->secret_key, token, strnlen(token, MAX_LEN)+1);
        } else if (!strncmp(token, "api_key", MAX_CMP)) {
            token = strtok(NULL, " ");
            auth_client->api_key = malloc(strnlen(token, MAX_LEN)+1);
            if (auth_client->api_key == NULL) {
                printf("Unable to allocate memory for api key.\n");
                exit(1);
            }
            strncpy(auth_client->api_key, token, strnlen(token, MAX_LEN)+1);
        } else if (!strncmp(token, "passphrase", MAX_CMP)) {
            token = strtok(NULL, " ");
            auth_client->passphrase = malloc(strnlen(token, MAX_LEN)+1);
            if (auth_client->passphrase == NULL) {
                printf("Unable to allocate memory for passphrase.\n");
                exit(1);
            }
            strncpy(auth_client->passphrase, token, strnlen(token, MAX_LEN)+1);
        }
    }

    fclose(fh);
    return auth_client;
}

struct Request *init_request(char *requestPath, char *method) {
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

struct Request *init_cb_request(char *requestPath, char *method) {
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

struct MemBuf *init_json_buffer() {
    struct MemBuf *json_buffer = (struct MemBuf *)malloc(sizeof(struct MemBuf));
    if (!json_buffer) {
        printf("Unable to allocate memory for json buffer");
        exit(1);
    }
    json_buffer->buffer = malloc(1);
    if (!json_buffer->buffer) {
        printf("Unable to allocate memory for json buffer.\n");
        exit(1);
    }
    json_buffer->size = 0;

    return json_buffer;
}

static void create_message(struct Request *request) {
    const size_t MAX_LEN = 100;

    time_t time_now = time(NULL);
    sprintf(request->timestamp, "%ld", time_now);

    strncpy(request->digest->message, request->timestamp, MAX_LEN);
    strncat(request->digest->message, request->method, MAX_LEN);
    strncat(request->digest->message, request->requestPath, MAX_LEN);
}

static void create_signature(struct Digest *digest, struct AuthClient *auth_client) {

    char hmac_key[65];
    int key_len = 64;

    EVP_DecodeBlock((unsigned char *)hmac_key,
                     (const unsigned char *)auth_client->secret_key,
                     strnlen(auth_client->secret_key, 100));

    unsigned char *hmac = NULL;
    unsigned int hmac_len;
    hmac = HMAC(EVP_sha256(),
                (const void *)hmac_key,
                key_len,
                (const unsigned char*)digest->message,
                strnlen(digest->message, 100),
                hmac,
                &hmac_len);

    EVP_EncodeBlock((unsigned char *)digest->sig,
                    (const unsigned char *)hmac,
                    hmac_len);
}

static struct curl_slist *set_headers(struct Request *request, struct AuthClient *auth_client) {
    create_message(request);
    create_signature(request->digest, auth_client);

    char cb_timestamp_header[100] = "cb-access-timestamp: ";
    strncat(cb_timestamp_header, request->timestamp, 100);

    char cb_access_header[100] = "cb-access-sign: ";
    strncat(cb_access_header, request->digest->sig, 100);

    char api_key_header[100] = "cb-access-key: ";
    strncat(api_key_header, auth_client->api_key, 100);

    char passphrase_header[100] = "cb-access-passphrase: ";
    strncat(passphrase_header, auth_client->passphrase, 100);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, api_key_header);
    headers = curl_slist_append(headers, passphrase_header);
    headers = curl_slist_append(headers, cb_access_header);
    headers = curl_slist_append(headers, cb_timestamp_header);

    if (!headers) {
        printf("Unable to format headers.\n");
        exit(1);
    }
    return headers;
}

void send_unauth_request(CURL *curl, struct Request *request, struct MemBuf *data) {
    curl_easy_setopt(curl, CURLOPT_URL, request->url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)data);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    free(request->digest);
    free(request);
}

void send_request(CURL *curl, struct Request *request, struct AuthClient *auth_client, struct MemBuf *data) {
    curl_easy_setopt(curl, CURLOPT_URL, request->url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)data);

    struct curl_slist *headers = set_headers(request, auth_client);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    free(request->digest);
    free(request);
}

size_t write_cb(char *contents, size_t itemsize, size_t nitems, void *stream) {
    size_t bytes = itemsize * nitems;
    struct MemBuf *buf = (struct MemBuf *)stream;

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
