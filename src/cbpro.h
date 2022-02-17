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
void get_accounts(struct Client *client);
void get_account_holds(struct Client *client, char *accountID);
void get_account_id(struct Client *client, char *accountID);
void get_account_ledger(struct Client *client, char *accountID);
void get_account_transfers(struct Client *client, char *accountID);

void get_coinbase_wallets(struct Client *client);
void generate_coinbase_address(struct Client *client, char *cbCryptoWalletID);

// Profiles
void get_profiles(struct Client *client);
void get_profile(struct Client *client, char *profileID);
void create_profile(struct Client *client, char *profileName);

// Payment methods and fees
void get_payment_methods(struct Client *client);
void get_fees(struct Client *client);
void get_fee_estimate(struct Client *client, char *currency, char *cbCryptoAddress);

// Transfers
void get_all_transfers(struct Client *client);
void get_single_transfer(struct Client *client, char *transferID);

// Orders
void get_all_fills(struct Client *client, char *currencyPair);


/*
 * Public requests sent to CoinbasePro API which are used unauthenticated.
*/

// Products
void get_all_products(struct Client *client);
void get_product(struct Client *client, char *currencyPair);
void get_product_book(struct Client *client, char *currencyPair);
void get_product_candles(struct Client *client, char *currencyPair);
void get_product_stats(struct Client *client, char *currencyPair);
void get_product_ticker(struct Client *client, char *currencyPair);
void get_product_trades(struct Client *client, char *currencyPair);

// Currencies
void get_currencies(struct Client *client);
void get_currency(struct Client *client, char *currency);
void get_signed_prices(struct Client *client);

#endif
