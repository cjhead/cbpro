#include "cbpro.h"

void get_accounts(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[10] = "/accounts";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_payment_methods(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[17] = "/payment-methods";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_profiles(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[10] = "/profiles";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_profile(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *profileID) {
    char requestPath[50] = "/profiles/";
    char method[4] = "GET";

    strcat(requestPath, profileID);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void create_profile(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *profileName) {
    char requestPath[50] = "/profiles";
    char method[5] = "POST";

    int len = strlen(profileName) + 13;

    char *post_data = malloc(sizeof(char *)*len);

    snprintf(post_data, len, "{\"name\":\"%s\"}", profileName);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);

    free(post_data);
}

void get_account_id(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID) {
    char requestPath[100] = "/accounts/";
    char method[4] = "GET";

    strcat(requestPath, accountID);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_account_holds(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID) {
    char requestPath[100] = "/accounts/";
    char method[4] = "GET";
    char url_post[7] = "/holds";

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_account_ledger(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID) {
    char requestPath[100] = "/accounts/";
    char url_post[8] = "/ledger";
    char method[4] = "GET";

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_account_transfers(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID) {
    char requestPath[100] = "/accounts/";
    char url_post[11] = "/transfers";
    char method[4] = "GET";

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_single_transfer(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *transferID) {
    char requestPath[100] = "/transfers/";
    char method[4] = "GET";

    strcat(requestPath, transferID);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_all_transfers(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[11] = "/transfers";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);

    send_request(curl, request, auth_client, data);
}

void get_coinbase_wallets(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[20] = "/coinbase-accounts/";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);

    send_request(curl, request, auth_client, data);
}

void get_fees(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data) {
    char requestPath[6] = "/fees";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);

    send_request(curl, request, auth_client, data);
}

void generate_coinbase_address(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *cbCryptoWalletID) {
    char requestPath[200] = "/coinbase-accounts/";
    char url_post[11] = "/addresses";
    char method[5] = "POST";

    strcat(requestPath, cbCryptoWalletID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_fee_estimate(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *currency, char *cbCryptoAddress) {
    char requestPath[100] = "/withdrawals/fee-estimate?currency=";
    char method[4] = "GET";
    strcat(requestPath, currency);
    strcat(requestPath, "&crypto_address=");
    strcat(requestPath, cbCryptoAddress);

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_all_fills(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *currencyPair) {
    char requestPath[100] = "/fills?product_id=";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, "&profile_id=default&limit=100");

    struct Request *request = init_request(requestPath, method);
    send_request(curl, request, auth_client, data);
}

void get_currencies(CURL *curl, struct MemBuf *data) {
    char requestPath[12] = "/currencies";
    char method[4] = "GET";
    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_currency(CURL *curl, struct MemBuf *data, char *currency) {
    char requestPath[25] = "/currencies/";
    char method[4] = "GET";

    strcat(requestPath, currency);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_all_products(CURL *curl, struct MemBuf *data) {
    char requestPath[10] = "/products";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product_book(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/book?level=1";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product_candles(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/candles?granularity=60";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product_stats(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/stats";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product_ticker(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/ticker";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_product_trades(CURL *curl, struct MemBuf *data, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/trades";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}

void get_signed_prices(CURL *curl, struct MemBuf *data) {
    char requestPath[8] = "/oracle";
    char method[4] = "GET";

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(curl, request, data);
}
