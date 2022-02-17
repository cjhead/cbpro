#include "cbpro.h"

void get_payment_methods(struct Client *client) {
    char requestPath[17] = "/payment-methods";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_profiles(struct Client *client) {
    char requestPath[10] = "/profiles";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_profile(struct Client *client, char *profileID) {
    char requestPath[50] = "/profiles/";
    char method[4] = "GET";

    strcat(requestPath, profileID);

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void create_profile(struct Client *client, char *profileName) {
    char requestPath[50] = "/profiles";
    char method[5] = "POST";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    int len = strlen(profileName) + 13;

    char *post_data = malloc(sizeof(char *)*len);

    snprintf(post_data, len, "{\"name\":\"%s\"}", profileName);

    curl_easy_setopt(client->session, CURLOPT_POSTFIELDS, post_data);
    struct Request *request = init_request(requestPath, method);
    send_request(request, client);

    free(post_data);
}

void get_account_id(struct Client *client, char *accountID) {
    char requestPath[100] = "/accounts/";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }

    data_buffer_reset(client->data);

    strcat(requestPath, accountID);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_accounts(struct Client *client) {
    char requestPath[10] = "/accounts";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_account_holds(struct Client *client, char *accountID) {
    char requestPath[100] = "/accounts/";
    char method[4] = "GET";
    char url_post[7] = "/holds";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_account_ledger(struct Client *client, char *accountID) {
    char requestPath[100] = "/accounts/";
    char url_post[8] = "/ledger";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_account_transfers(struct Client *client, char *accountID) {
    char requestPath[100] = "/accounts/";
    char url_post[11] = "/transfers";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, accountID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_single_transfer(struct Client *client, char *transferID) {
    char requestPath[100] = "/transfers/";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, transferID);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_all_transfers(struct Client *client) {
    char requestPath[11] = "/transfers";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);

    send_request(request, client);
}

void get_coinbase_wallets(struct Client *client) {
    char requestPath[20] = "/coinbase-accounts/";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);

    send_request(request, client);
}

void get_fees(struct Client *client) {
    char requestPath[6] = "/fees";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);

    send_request(request, client);
}

void generate_coinbase_address(struct Client *client, char *cbCryptoWalletID) {
    char requestPath[200] = "/coinbase-accounts/";
    char url_post[11] = "/addresses";
    char method[5] = "POST";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, cbCryptoWalletID);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_fee_estimate(struct Client *client, char *currency, char *cbCryptoAddress) {
    char requestPath[100] = "/withdrawals/fee-estimate?currency=";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, currency);
    strcat(requestPath, "&crypto_address=");
    strcat(requestPath, cbCryptoAddress);

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_all_fills(struct Client *client, char *currencyPair) {
    char requestPath[100] = "/fills?product_id=";
    char method[4] = "GET";

    if(client->authenticated == false) {
        puts("Client is unauthenticated.");
        puts("Call the function 'authorize_client' and try again.\n");
        exit(1);
    }
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, "&profile_id=default&limit=100");

    struct Request *request = init_request(requestPath, method);
    send_request(request, client);
}

void get_currencies(struct Client *client) {
    char requestPath[12] = "/currencies";
    char method[4] = "GET";
    data_buffer_reset(client->data);
    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_currency(struct Client *client, char *currency) {
    char requestPath[25] = "/currencies/";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currency);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_all_products(struct Client *client) {
    char requestPath[10] = "/products";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product_book(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/book?level=1";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product_candles(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/candles?granularity=60";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product_stats(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/stats";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product_ticker(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/ticker";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_product_trades(struct Client *client, char *currencyPair) {
    char requestPath[25] = "/products/";
    char url_post[25] = "/trades";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    strcat(requestPath, currencyPair);
    strcat(requestPath, url_post);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}

void get_signed_prices(struct Client *client) {
    char requestPath[8] = "/oracle";
    char method[4] = "GET";
    data_buffer_reset(client->data);

    struct Request *request = init_request(requestPath, method);
    send_unauth_request(client, request);
}
