#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cbpro.h"

void exchange_rates(struct Client *client, char *currency) {
    char requestPath[60] = "/exchange-rates?currency=";

    strcat(requestPath, currency);

    send_cb_unauth_request(client, requestPath, GET);
}

void spot_price(struct Client *client, char *currencyPair) {
    size_t len;
    char *prices = "/prices/";
    char *spot = "/spot";

    len = strlen(prices)+strlen(currencyPair)+strlen(spot)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", prices, currencyPair, spot);

    send_cb_unauth_request(client, requestPath, GET);
    free(requestPath);
}
