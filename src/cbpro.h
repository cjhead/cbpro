#ifndef CBPRO_H
#define CBPRO_H

#include <curl/curl.h>
#include <stdbool.h>

enum Method {
    GET,
    POST,
    PUT,
    DELETE
};

enum cbproError {
    SUCCESS,
    FILE_NOT_FOUND,
    FAILED_MEMORY_ALLOCATION,
    NOT_AUTHORIZED,
    TOTAL_ERRORS
};

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
    struct DataBuf *data;
};

struct DataBuf {
    char *buffer;
    size_t size;
};

/*
 * Client functions
*/

struct Client *client_create();
int authorize_client(FILE *fh, struct Client *client);
void client_cleanup(struct Client *client);

/*
 * CoinbasePro API request functions which require authentication.
*/

// Accounts
int get_accounts(struct Client *client);
int get_account_holds(struct Client *client, char *accountID);
int get_account_id(struct Client *client, char *accountID);
int get_account_ledger(struct Client *client, char *accountID);
int get_account_transfers(struct Client *client, char *accountID);

int get_coinbase_wallets(struct Client *client);
int generate_coinbase_address(struct Client *client, char *cbCryptoWalletID);

// Profiles
int get_profiles(struct Client *client);
int get_profile(struct Client *client, char *profileID);
int create_profile(struct Client *client, char *profileName);

// Payment methods and fees
int get_payment_methods(struct Client *client);
int get_fees(struct Client *client);
int get_fee_estimate(struct Client *client, char *currency, char *cbCryptoAddress);

// Transfers
int get_all_transfers(struct Client *client);
int get_single_transfer(struct Client *client, char *transferID);

// Orders
int get_all_fills(struct Client *client, char *currencyPair);

/*
 * Public requests sent to CoinbasePro API which are used unauthenticated.
*/

// Products
int get_all_products(struct Client *client);
int get_product(struct Client *client, char *currencyPair);
int get_product_book(struct Client *client, char *currencyPair);
int get_product_candles(struct Client *client, char *currencyPair);
int get_product_stats(struct Client *client, char *currencyPair);
int get_product_ticker(struct Client *client, char *currencyPair);
int get_product_trades(struct Client *client, char *currencyPair);

// Currencies
int get_currencies(struct Client *client);
int get_currency(struct Client *client, char *currency);
int get_signed_prices(struct Client *client);

/*
 * Coinbase API - Unauthenticated
*/

void exchange_rates(struct Client *client, char *currency);
void spot_price(struct Client *client, char *currencyPair);

/*
 * General session handling - Need to be abstracted
*/
// void send_request(struct Client *client, char *requestPath, enum Method req_method);
void send_request(struct Client *client, const char *requestPath, enum Method req_method);
void send_unauth_request(struct Client *client, const char *requestPath, enum Method req_method);
void send_cb_unauth_request(struct Client *client, const char *requestPath, enum Method req_method);

/*
 * Error handling
*/
void errorMsg(int error);

#endif
