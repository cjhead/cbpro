#include <stdlib.h>
#include "../../src/cbpro.h"

int main(void) {

    struct Client *client = client_create();

    get_all_products(client);
    printf("%s\n", client->data->buffer);

    client_cleanup(client);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
