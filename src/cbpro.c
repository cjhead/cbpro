#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "cbpro.h"

struct requestPaths {
    const char *accounts;
    const char *profiles;
    const char *paymentMethods;
    const char *currencies;
    const char *products;
    const char *transfers;
    const char *cbAccounts;
    const char *fees;
    const char *oracle;
} paths = {
"/accounts/",
"/profiles/",
"/payment-methods",
"/currencies/",
"/products/",
"/transfers/",
"/coinbase-accounts/",
"/fees",
"/oracle",
};

int get_payment_methods(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, paths.paymentMethods, GET);
    return(0);
}

int get_profiles(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, paths.profiles, GET);
    return(0);
}

int get_profile(struct Client *client, char *profileID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(paths.profiles)+strlen(profileID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", paths.profiles, profileID);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int create_profile(struct Client *client, char *profileName) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    char *requestPath = malloc(strlen(paths.profiles)+strlen(profileName)+1);

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

    send_request(client, paths.accounts, GET);
    return(0);
}

int get_account_id(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(paths.accounts)+strlen(accountID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", paths.accounts, accountID);

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

    len = strlen(paths.accounts)+strlen(accountID)+strlen(holds)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.accounts, accountID, holds);

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

    len = strlen(paths.accounts)+strlen(accountID)+strlen(ledger)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.accounts, accountID, ledger);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_account_transfers(struct Client *client, char *accountID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(paths.accounts)+strlen(accountID)+strlen(paths.transfers)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.accounts, accountID, paths.transfers);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_single_transfer(struct Client *client, char *transferID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;

    len = strlen(paths.transfers)+strlen(transferID)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", paths.transfers, transferID);

    send_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_all_transfers(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, paths.transfers, GET);
    return(0);
}

int get_coinbase_wallets(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, paths.cbAccounts, GET);
    return(0);
}

int get_fees(struct Client *client) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    send_request(client, paths.fees, GET);
    return(0);
}

int generate_coinbase_address(struct Client *client, char *cbCryptoWalletID) {
    if(client->authenticated == false) {
        return(NOT_AUTHORIZED);
    }

    size_t len;
    char *addresses = "/addresses";

    len = strlen(paths.cbAccounts)+strlen(cbCryptoWalletID)+strlen(addresses)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.cbAccounts, cbCryptoWalletID, addresses);

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

    send_unauth_request(client, paths.currencies, GET);
    return(0);
}

int get_currency(struct Client *client, char *currency) {
    size_t len;

    len = strlen(paths.currencies)+strlen(currency)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", paths.currencies, currency);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_all_products(struct Client *client) {

    send_unauth_request(client, paths.products, GET);
    return(0);
}

int get_product(struct Client *client, char *currencyPair) {
    size_t len;

    len = strlen(paths.products)+strlen(currencyPair)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s", paths.products, currencyPair);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_book(struct Client *client, char *currencyPair) {
    size_t len;
    char *book_level = "/book?level=1";

    len = strlen(paths.products)+strlen(currencyPair)+strlen(book_level)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.products, currencyPair, book_level);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_candles(struct Client *client, char *currencyPair) {
    size_t len;
    char *candle_gran = "/candles?granularity=60";

    len = strlen(paths.products)+strlen(currencyPair)+strlen(candle_gran)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.products, currencyPair, candle_gran);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_stats(struct Client *client, char *currencyPair) {
    size_t len;
    char *stats = "/stats";

    len = strlen(paths.products)+strlen(currencyPair)+strlen(stats)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.products, currencyPair, stats);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_ticker(struct Client *client, char *currencyPair) {
    size_t len;
    char *ticker = "/ticker";

    len = strlen(paths.products)+strlen(currencyPair)+strlen(ticker)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.products, currencyPair, ticker);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_product_trades(struct Client *client, char *currencyPair) {
    size_t len;
    char *trades = "/trades";

    len = strlen(paths.products)+strlen(currencyPair)+strlen(trades)+1;
    char *requestPath = malloc(len);
    snprintf(requestPath, len, "%s%s%s", paths.products, currencyPair, trades);

    send_unauth_request(client, requestPath, GET);
    free(requestPath);
    return(0);
}

int get_signed_prices(struct Client *client) {

    send_unauth_request(client, paths.oracle, GET);
    return(0);
}
