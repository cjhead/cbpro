#ifndef CB_H
#define CB_H

#include <string.h>
#include <stdbool.h>
#include "utils.h"


/*
 * Coinbase API
*/

void exchange_rates(struct Client *client, char *currency);
void spot_price(struct Client *client, char *currencyPair);

#endif
