#ifndef CB_H
#define CB_H

#include <string.h>
#include <stdbool.h>
#include "utils.h"


/*
 * Coinbase API
*/

void exchange_rates(CURL *curl, struct DataBuf *data, char *currency);
void spot_price(CURL *curl, struct DataBuf *data, char *currencyPair);

#endif
