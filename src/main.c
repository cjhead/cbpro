#include "cb.h"
#include "cbpro.h"
#include "utils.h"
#include <cjson/cJSON.h>

int main(void) {

    const char *cred_file = "creds.txt";
    struct AuthClient *auth_client = create_auth_client(cred_file);

    char *accountID = "********-****-****-****-************";
    char *transferID = "********-****-****-****-************";
    char *profileID = "********-****-****-****-************";
    char *profileName = "Test_Profile";
    char *currency = "BTC";
    char *currencyPair = "BTC-USD";
    char *cbCryptoAddress = "***********************************";
    char *cbCryptoWalletID = "************************************";

    struct MemBuf *data = init_json_buffer();
    struct Params *params = malloc(sizeof(struct Params));

    strncpy(params->accountID, accountID, 50);
    strncpy(params->transferID, transferID, 50);
    strncpy(params->profileID, profileID, 50);
    strncpy(params->profileName, profileName, 50);
    strncpy(params->currency, currency, 50);
    strncpy(params->currencyPair, currencyPair, 50);
    strncpy(params->cbCryptoAddress, cbCryptoAddress, 50);
    strncpy(params->cbCryptoWalletID, cbCryptoWalletID, 50);


    CURL *curl = init_session();



/*
    Authorized Access Only
*/

    // get_accounts(curl, auth_client, data);
    // get_account_id(curl, auth_client, data, accountID);
    // get_account_holds(curl, auth_client, data, accountID);
    // get_account_ledger(curl, auth_client, data, accountID);
    // get_account_transfers(curl, auth_client, data, accountID);

    // get_all_transfers(curl, auth_client, data);
    // get_single_transfer(curl, auth_client, data, transferID);

    // get_fees(curl, auth_client, data);
    // get_payment_methods(curl, auth_client, data);
    // get_coinbase_wallets(curl, auth_client, data);
    // generate_coinbase_address(curl, auth_client, data, cbCryptoWalletID);

    // get_profiles(curl, auth_client, data);
    // get_profile(curl, auth_client, data, profileID);
    // create_profile(curl, auth_client, data, profileName);

    // get_fee_estimate(curl, auth_client, data, currency, cbCryptoAddress);

    // get_all_fills(curl, auth_client, data, currencyPair);

/*
    Public Access
*/

    // Products
    get_all_products(curl, data);
    // get_product(curl, data, currencyPair);
    // get_product_book(curl, data, currencyPair);
    // get_product_candles(curl, data, currencyPair);
    // get_product_stats(curl, data, currencyPair);
    // get_product_ticker(curl, data, currencyPair);
    // get_product_trades(curl, data, currencyPair);


    //Currencies
    // get_currencies(curl, data);
    // get_currency(curl, data, currency);

    // Signed prices from Oracle
    // get_signed_prices(curl, data);

/*
Coinbase API
*/

    // spot_price(curl, data, currencyPair);
    // exchange_rates(curl, data, currency);



    cJSON *json = cJSON_Parse(data->buffer);
    char *result = cJSON_Print(json);

    printf("%s\n", result);

    cJSON_Delete(json);
    free(result);

    free(data->buffer);
    free(data);
    free(params);
    free(auth_client->api_key);
    free(auth_client->passphrase);
    free(auth_client->secret_key);
    free(auth_client);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
