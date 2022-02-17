#ifndef CBPRO_H
#define CBPRO_H

#include <stdio.h>
#include <curl/curl.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <string.h>
#include "utils.h"

/*
 * CoinbasePro API request functions which require authentication.
*/

// Accounts
void get_accounts(struct Client *client, struct MemBuf *data);
void get_account_holds(struct Client *client, struct MemBuf *data, char *accountID);
void get_account_id(struct Client *client, struct MemBuf *data, char *accountID);
void get_account_ledger(struct Client *client, struct MemBuf *data, char *accountID);
void get_account_transfers(struct Client *client, struct MemBuf *data, char *accountID);

void get_coinbase_wallets(struct Client *client, struct MemBuf *data);
void generate_coinbase_address(struct Client *client, struct MemBuf *data, char *cbCryptoWalletID);

// Profiles
void get_profiles(struct Client *client, struct MemBuf *data);
void get_profile(struct Client *client, struct MemBuf *data, char *profileID);
void create_profile(struct Client *client, struct MemBuf *data, char *profileName);

// Payment methods and fees
void get_payment_methods(struct Client *client, struct MemBuf *data);
void get_fees(struct Client *client, struct MemBuf *data);
void get_fee_estimate(struct Client *client, struct MemBuf *data, char *currency, char *cbCryptoAddress);

// Transfers
void get_all_transfers(struct Client *client, struct MemBuf *data);
void get_single_transfer(struct Client *client, struct MemBuf *data, char *transferID);

// Orders
void get_all_fills(struct Client *client, struct MemBuf *data, char *currencyPair);


/*
 * Public requests sent to CoinbasePro API which are used unauthenticated.
*/

// Products
void get_all_products(struct Client *client, struct MemBuf *data);
void get_product(struct Client *client, struct MemBuf *data, char *currencyPair);
void get_product_book(struct Client *client, struct MemBuf *data, char *currencyPair);
void get_product_candles(struct Client *client, struct MemBuf *data, char *currencyPair);
void get_product_stats(struct Client *client, struct MemBuf *data, char *currencyPair);
void get_product_ticker(struct Client *client, struct MemBuf *data, char *currencyPair);
void get_product_trades(struct Client *client, struct MemBuf *data, char *currencyPair);

// Currencies
void get_currencies(struct Client *client, struct MemBuf *data);
void get_currency(struct Client *client, struct MemBuf *data, char *currency);
void get_signed_prices(struct Client *client, struct MemBuf *data);

#endif
