#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "cbpro.h"

#define ACCOUNTS "/accounts/"
#define PROFILES "/profiles/"
#define PAYMENT_METHODS "/payment-methods/"
#define CURRENCIES "/currencies/"
#define PRODUCTS "/products/"
#define TRANSFERS "/transfers/"
#define CBACCOUNTS "/coinbase-accounts/"
#define FEES "/fees"
#define ORACLE "/oracle"

int get_payment_methods(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, PAYMENT_METHODS, GET);
    return(0);
}

int get_profiles(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, PROFILES, GET);
    return(0);
}

int get_profile(struct Client *client, char *profileID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(PROFILES)+strlen(profileID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", PROFILES, profileID);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int create_profile(struct Client *client, char *profileName) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char *requestPath = malloc(strlen(PROFILES)+strlen(profileName)+1);

    size_t len = strlen(profileName) + 13;
    char *post_data = malloc(len);

    snprintf(post_data, len, "{\"name\":\"%s\"}", profileName);

    curl_easy_setopt(client->session, CURLOPT_POSTFIELDS, post_data);
    send_request(client, requestPath, POST);

    free(post_data);
    free(requestPath);
    return(0);
}

int get_accounts(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, ACCOUNTS, GET);
    return(0);
}

int get_account_id(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(ACCOUNTS)+strlen(accountID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", ACCOUNTS, accountID);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_account_holds(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *holds = "/holds";

    len = strlen(ACCOUNTS)+strlen(accountID)+strlen(holds)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", ACCOUNTS, accountID, holds);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_account_ledger(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *ledger = "/ledger";

    len = strlen(ACCOUNTS)+strlen(accountID)+strlen(ledger)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", ACCOUNTS, accountID, ledger);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_account_transfers(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(ACCOUNTS)+strlen(accountID)+strlen(TRANSFERS)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", ACCOUNTS, accountID, TRANSFERS);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_single_transfer(struct Client *client, char *transferID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(TRANSFERS)+strlen(transferID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", TRANSFERS, transferID);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_all_transfers(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, TRANSFERS, GET);
    return(0);
}

int get_coinbase_wallets(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, CBACCOUNTS, GET);
    return(0);
}

int get_fees(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, FEES, GET);
    return(0);
}

int generate_coinbase_address(struct Client *client, char *cbCryptoWalletID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *addresses = "/addresses";

    len = strlen(CBACCOUNTS)+strlen(cbCryptoWalletID)+strlen(addresses)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", CBACCOUNTS, cbCryptoWalletID, addresses);

    send_request(client, requestPath, POST);
    free(requestPath);
    return(0);
}

int get_fee_estimate(struct Client *client, char *currency, char *cbCryptoAddress) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *estimate = "/withdrawals/fee-estimate?currency=";
    char *address_p = "&crypto_address=";

    len = strlen(estimate)+strlen(currency)+strlen(address_p)+strlen(cbCryptoAddress)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s%s", estimate, currency, address_p, cbCryptoAddress);
    printf("%s\n", requestPath);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_all_fills(struct Client *client, char *currencyPair) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *fills = "/fills?product_id=";
    char *limit = "&profile_id=default&limit=100";

    len = strlen(fills)+strlen(currencyPair)+strlen(limit)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", fills, currencyPair, limit);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_currencies(struct Client *client) {

    send_unauth_request(client, CURRENCIES, GET);
    return(0);
}

int get_currency(struct Client *client, char *currency) {
    size_t len;

    len = strlen(CURRENCIES)+strlen(currency)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", CURRENCIES, currency);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_all_products(struct Client *client) {

    send_unauth_request(client, PRODUCTS, GET);
    return(0);
}

int get_product(struct Client *client, char *currencyPair) {
    size_t len;

    len = strlen(PRODUCTS)+strlen(currencyPair)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", PRODUCTS, currencyPair);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_book(struct Client *client, char *currencyPair) {
    size_t len;
    char *book_level = "/book?level=1";

    len = strlen(PRODUCTS)+strlen(currencyPair)+strlen(book_level)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", PRODUCTS, currencyPair, book_level);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_candles(struct Client *client, char *currencyPair) {
    size_t len;
    char *candle_gran = "/candles?granularity=60";

    len = strlen(PRODUCTS)+strlen(currencyPair)+strlen(candle_gran)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", PRODUCTS, currencyPair, candle_gran);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_stats(struct Client *client, char *currencyPair) {
    size_t len;
    char *stats = "/stats";

    len = strlen(PRODUCTS)+strlen(currencyPair)+strlen(stats)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", PRODUCTS, currencyPair, stats);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_ticker(struct Client *client, char *currencyPair) {
    size_t len;
    char *ticker = "/ticker";

    len = strlen(PRODUCTS)+strlen(currencyPair)+strlen(ticker)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", PRODUCTS, currencyPair, ticker);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_trades(struct Client *client, char *currencyPair) {
    size_t len;
    char *trades = "/trades";

    len = strlen(PRODUCTS)+strlen(currencyPair)+strlen(trades)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", PRODUCTS, currencyPair, trades);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_signed_prices(struct Client *client) {

    send_unauth_request(client, ORACLE, GET);
    return(0);
}
