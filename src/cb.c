#include "cb.h"

void exchange_rates(struct Client *client, char *currency) {
    char requestPath[60] = "/exchange-rates?currency=";

    strcat(requestPath, currency);

    send_unauth_request(client, requestPath, GET);
}

void spot_price(struct Client *client, char *currencyPair) {
    char requestPath[60] = "/prices/";
    char url_post[6] = "/spot";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
}
