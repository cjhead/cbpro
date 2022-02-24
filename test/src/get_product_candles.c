#include <stdlib.h>
#include "../../src/cbpro.h"

int main(void) {

    struct Client *client = client_create();
    char *currencyPair = "BTC-USD";

    get_product_candles(client, currencyPair);
    printf("%s\n", client->data->buffer);

    client_cleanup(client);

    return EXIT_SUCCESS;
}
