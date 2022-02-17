#include "cb.h"

void exchange_rates(CURL *curl, struct DataBuf *data, char *currency) {
    char requestPath[60] = "/exchange-rates?currency=";
    char method[4] = "GET";

    strcat(requestPath, currency);

    struct Request *request = init_cb_request(requestPath, method);
    send_unauth_request(curl, request);
}

void spot_price(CURL *curl, struct DataBuf *data, char *currencyPair) {
    char requestPath[60] = "/prices/";
    char url_post[6] = "/spot";
    char method[4] = "GET";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_cb_request(requestPath, method);
    send_unauth_request(curl, request);
}
