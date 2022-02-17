#include "cb.h"
#include "cbpro.h"
#include "utils.h"
//#include <cjson/cJSON.h>

int main(void) {

    struct MemBuf *data = init_json_buffer();

    struct Client *client = malloc(sizeof(struct Client));
    client->session = init_session();
    client->authenticated = false;

    /*
     * Call these to authenticate the client
    */

    // const char *cred_file = "creds.txt";
    // authorize_client(cred_file, client);

    /*
     * Examples
    */
    // char *accountID = "********-****-****-****-************";
    // char *transferID = "********-****-****-****-************";
    // char *profileID = "********-****-****-****-************";
    // char *currency = "BTC";
    // char *currencyPair = "BTC-USD";
    // char *cbCryptoAddress = "**********************************";
    // char *cbCryptoWalletID = "********-****-****-****-************";




    /*
     * Authorized Access Only
    */

    // get_accounts(client, data);
    // get_account_id(client, data, accountID);
    // get_account_holds(client, data, accountID);
    // get_account_ledger(client, data, accountID);
    // get_account_transfers(client, data, accountID);

    // get_all_transfers(client, data);
    // get_single_transfer(client, data, transferID);

    // get_fees(client, data);
    // get_payment_methods(client, data);
    // get_payment_methods(client, data);
    // get_coinbase_wallets(client, data);
    // generate_coinbase_address(client, data, cbCryptoWalletID);

    // get_profiles(client, data);
    // get_profile(client, data, profileID);
    // create_profile(client, data, profileName);

    // get_fee_estimate(client, data, currency, cbCryptoAddress);
    // get_all_fills(client, data, currencyPair);

    /*
     * Public Access
    */

    // Products
    // get_all_products(client, data);
    // get_product(client, data, currencyPair);
    // get_product_book(client, data, currencyPair);
    // get_product_candles(client, data, currencyPair);
    // get_product_stats(client, data, currencyPair);
    // get_product_ticker(client, data, currencyPair);
    // get_product_trades(client, data, currencyPair);


    // Currencies
    // get_currencies(client, data);
    // get_currency(client, data, currency);

    // Signed prices from Oracle
    // get_signed_prices(client, data);

    /*
     * Coinbase API
    */

    // spot_price(client, data, currencyPair);
    // exchange_rates(client, data, currency);

    /*
     *  Results
    */

    // Unformatted and doesn't rely on cJSON
    printf("%s\n", data->buffer);

    // Formatted with cJSON
    // cJSON *json = cJSON_Parse(data->buffer);
    // char *result = cJSON_Print(json);
    //
    // printf("%s\n", result);
    //
    // cJSON_Delete(json);
    // free(result);

    free(data->buffer);
    free(data);

    client_cleanup(client);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
