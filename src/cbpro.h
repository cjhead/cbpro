#ifndef CBPRO_H
#define CBPRO_H

#include <stdio.h>
#include <curl/curl.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <string.h>
#include "utils.h"

/*
CoinbasePro API request functions which require authentication.
*/
void get_accounts(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void get_account_holds(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID);
void get_account_id(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID);
void get_account_ledger(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID);
void get_account_transfers(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *accountID);

void get_coinbase_wallets(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void generate_coinbase_address(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *cbCryptoWalletID);

// Profiles
void get_profiles(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void get_profile(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *profileID);
// Create_profile gives me forbidden access message?
void create_profile(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *profileName);



void get_payment_methods(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void get_fees(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void get_all_transfers(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data);
void get_single_transfer(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *transferID);
void get_fee_estimate(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *currency, char *cbCryptoAddress);

// Orders
void get_all_fills(CURL *curl, struct AuthClient *auth_client, struct MemBuf *data, char *currencyPair);


/*
Public requests sent to CoinbasePro API which are used unauthenticated.
*/
// Products
void get_all_products(CURL *curl, struct MemBuf *data);
void get_product(CURL *curl, struct MemBuf *data, char *currencyPair);
void get_product_book(CURL *curl, struct MemBuf *data, char *currencyPair);
void get_product_candles(CURL *curl, struct MemBuf *data, char *currencyPair);
void get_product_stats(CURL *curl, struct MemBuf *data, char *currencyPair);
void get_product_ticker(CURL *curl, struct MemBuf *data, char *currencyPair);
void get_product_trades(CURL *curl, struct MemBuf *data, char *currencyPair);

// Currencies
void get_currencies(CURL *curl, struct MemBuf *data);
void get_currency(CURL *curl, struct MemBuf *data, char *currency);
void get_signed_prices(CURL *curl, struct MemBuf *data);

#endif
