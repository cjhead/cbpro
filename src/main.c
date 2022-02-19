#include <stdlib.h>
#include "cb.h"
#include "cbpro.h"
#include "utils.h"
#include "cbpro_err.h"
//#include <cjson/cJSON.h>

int main(void) {

    struct Client *client = client_create();

    // Call these to authenticate the client
    // const char *cred_file = "creds.txt";
    // authorize_client(cred_file, client);

    // Example Parameters
    // char *accountID = "********-****-****-****-************";
    // char *transferID = "********-****-****-****-************";
    // char *profileID = "********-****-****-****-************";
    // char *currency = "BTC";
    // char *currencyPair = "BTC-USD";
    // char *cbCryptoAddress = "**********************************";
    // char *cbCryptoWalletID = "********-****-****-****-************";

     /*************************
     * Authorized Access Only *
     *************************/

    // get_accounts(client);
    // get_account_id(client, accountID);
    // get_account_holds(client, accountID);
    // get_account_ledger(client, accountID);
    // get_account_transfers(client, accountID);

    // get_all_transfers(client);
    // get_single_transfer(client, transferID);

    // get_fees(client);
    // get_payment_methods(client);
    // get_coinbase_wallets(client);
    // generate_coinbase_address(client, cbCryptoWalletID);

    // get_profiles(client);
    // get_profile(client, profileID);
    // create_profile(client, profileName);

    // get_fee_estimate(client, currency, cbCryptoAddress);
    // get_all_fills(client, currencyPair);

     /****************
     * Public Access *
     ****************/

    // Products
    // get_all_products(client);
    // get_product(client, currencyPair);
    // get_product_book(client, currencyPair);
    // get_product_candles(client, currencyPair);
    // get_product_stats(client, currencyPair);
    // get_product_ticker(client, currencyPair);
    // get_product_trades(client, currencyPair);

    // Currencies
    // get_currencies(client);
    // get_currency(client, currency);

    // Signed prices from Oracle
    // get_signed_prices(client);

     /***************
     * Coinbase API *
     ***************/

    // spot_price(client, currencyPair);
    // exchange_rates(client, currency);

     /**********
     * Results *
     **********/

    // Print results to stdout, unformatted
    // printf("%s\n", client->data->buffer);

    // Formatted with cJSON
    // cJSON *json = cJSON_Parse(data->buffer);
    // char *result = cJSON_Print(json);
    //
    // printf("%s\n", result);
    //
    // cJSON_Delete(json);
    // free(result);


    /**********
    * Cleanup *
    **********/

    client_cleanup(client);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
