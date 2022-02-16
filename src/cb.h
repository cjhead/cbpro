#ifndef CB_H
#define CB_H

#include <string.h>
#include "utils.h"


void exchange_rates(CURL *curl, struct MemBuf *data, char *currency);
void spot_price(CURL *curl, struct MemBuf *data, char *currencyPair);

#endif
