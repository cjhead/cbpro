#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <curl/curl.h>
#include <stdarg.h>

enum method {
    GET,
    POST,
    PUT,
    DELETE
};

struct AuthClient {
    char *secret_key;
    char *api_key;
    char *passphrase;
};

struct Digest {
    char message[300];
    char sig[45];
};

struct Params {
    char accountID[50];
    char transferID[50];
    char profileID[50];
    char profileName[50];
    char currency[10];
    char currencyPair[20];
    char cbCryptoAddress[50];
    char cbCryptoWalletID[50];
};

struct Request {
    char method[10];
    char requestPath[200];
    char url[200];
    char timestamp[11];
    struct Digest *digest;
};

struct MemBuf {
    char *buffer;
    size_t size;
};

/*
Initializes an authenticated client from credentials found in filename.
*/
struct AuthClient *create_auth_client(const char *filename);
struct Request *init_request(char *requestPath, char *method);
struct Request *init_cb_request(char *requestPath, char *method);

/*
Constructs the message sent to the coinbase API:
    The Secret Key is first base64 decoded.
    The result is used to sign the HMAC which uses a sha256 digest.
    This output is then base64 encoded.
*/
static void create_message(struct Request *request);
static void create_signature(struct Digest *digest, struct AuthClient *auth_client);

CURL *init_session();
static struct curl_slist *set_headers();
struct MemBuf *init_json_buffer();
// char *send_request(CURL *curl, struct Request *request, struct AuthClient *auth_client);
// struct MemBuf *send_request(CURL *curl, struct Request *request, struct AuthClient *auth_client);
void send_request(CURL *curl, struct Request *request, struct AuthClient *auth_client, struct MemBuf *data);
void send_unauth_request(CURL *curl, struct Request *request, struct MemBuf *data);
size_t write_cb(char *contents, size_t itemsize, size_t nitems, void *stream);

#endif
