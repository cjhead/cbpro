#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <stdarg.h>

struct Credentials {
    char *secret_key;
    char *api_key;
    char *passphrase;
};

struct Client {
    char *api_url;
    CURL *session;
    bool authenticated;
    struct Credentials *creds;
};

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

struct MemBuf {
    char *buffer;
    size_t size;
};

/*
Initializes an authenticated client from credentials found in filename.
*/
void authorize_client(const char *filename, struct Client *client);
struct AuthClient *create_auth_client(const char *filename);
struct Request *init_request(char *requestPath, char *method);
struct Request *init_cb_request(char *requestPath, char *method);
void client_cleanup(struct Client *client);

/*
Constructs the message sent to the coinbase API:
    The Secret Key is first base64 decoded.
    The result is used to sign the HMAC which uses a sha256 digest.
    This output is then base64 encoded.
*/
void create_message(struct Request *request);
void create_signature(struct Digest *digest, struct Client *client);

CURL *init_session();
struct curl_slist *set_headers(struct Request *request, struct Client *client);
struct MemBuf *init_json_buffer();
void send_request(struct Request *request, struct Client *client, struct MemBuf *data);
void send_unauth_request(struct Client *client, struct Request *request, struct MemBuf *data);
size_t write_cb(char *contents, size_t itemsize, size_t nitems, void *stream);

#endif
