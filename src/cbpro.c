#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "cbpro.h"

int get_payment_methods(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[17] = "/payment-methods";
    send_request(client, requestPath, GET);
    return(0);
}

int get_profiles(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[10] = "/profiles";
    send_request(client, requestPath, GET);
    return(0);
}

int get_profile(struct Client *client, char *profileID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[50] = "/profiles/";
    strcat(requestPath, profileID);
    send_request(client, requestPath, GET);
    return(0);
}

int create_profile(struct Client *client, char *profileName) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[50] = "/profiles";

    int len = strlen(profileName) + 13;
    char *post_data = malloc(sizeof(char *)*len);

    snprintf(post_data, len, "{\"name\":\"%s\"}", profileName);

    curl_easy_setopt(client->session, CURLOPT_POSTFIELDS, post_data);
    send_request(client, requestPath, POST);

    free(post_data);
    return(0);
}

int get_account_id(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/accounts/";
    strcat(requestPath, accountID);

    send_request(client, requestPath, GET);
    return(0);
}


int get_accounts(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[10] = "/accounts";
    send_request(client, requestPath, GET);
    return(0);
}

int get_account_holds(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/accounts/";
    char url_post[7] = "/holds";
    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    send_request(client, requestPath, GET);
    return(0);
}

int get_account_ledger(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/accounts/";
    char url_post[8] = "/ledger";
    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    send_request(client, requestPath, GET);
    return(0);
}

int get_account_transfers(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/accounts/";
    char url_post[11] = "/transfers";
    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    send_request(client, requestPath, GET);
    return(0);
}

int get_single_transfer(struct Client *client, char *transferID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/transfers/";
    strcat(requestPath, transferID);

    send_request(client, requestPath, GET);
    return(0);
}

int get_all_transfers(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[11] = "/transfers";
    send_request(client, requestPath, GET);
    return(0);
}

int get_coinbase_wallets(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[20] = "/coinbase-accounts/";
    send_request(client, requestPath, GET);
    return(0);
}

int get_fees(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[6] = "/fees";
    send_request(client, requestPath, GET);
    return(0);
}

int generate_coinbase_address(struct Client *client, char *cbCryptoWalletID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[200] = "/coinbase-accounts/";
    char url_post[11] = "/addresses";
    strcat(requestPath, cbCryptoWalletID);
    strcat(requestPath, url_post);

    send_request(client, requestPath, POST);
    return(0);
}

int get_fee_estimate(struct Client *client, char *currency, char *cbCryptoAddress) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/withdrawals/fee-estimate?currency=";
    strcat(requestPath, currency);
    strcat(requestPath, "&crypto_address=");
    strcat(requestPath, cbCryptoAddress);

    send_request(client, requestPath, GET);
    return(0);
}

int get_all_fills(struct Client *client, char *currencyPair) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char requestPath[100] = "/fills?product_id=";
    strcat(requestPath, currencyPair);
    strcat(requestPath, "&profile_id=default&limit=100");

    send_request(client, requestPath, GET);
    return(0);
}

int get_currencies(struct Client *client) {
    char requestPath[12] = "/currencies";

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_currency(struct Client *client, char *currency) {
    char requestPath[25] = "/currencies/";
    strcat(requestPath, currency);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_all_products(struct Client *client) {
    char requestPath[10] = "/products";

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    strcat(requestPath, currencyPair);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product_book(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/book?level=1";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product_candles(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/candles?granularity=60";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product_stats(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/stats";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product_ticker(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/ticker";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_product_trades(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/trades";

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    send_unauth_request(client, requestPath, GET);
    return(0);
}

int get_signed_prices(struct Client *client) {
    char requestPath[8] = "/oracle";

    send_unauth_request(client, requestPath, GET);
    return(0);
}
