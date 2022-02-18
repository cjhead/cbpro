#include <stdio.h>
#include "cbpro_err.h"

static const char *cbproErrorMsg[] = {
    "SUCCESS",
    "File not found",
    "Failed memory allocation",
    "Client has not been authorized",
    "TOTAL ERRORS"
};

void errorMsg(int error) {
    if( error && error > SUCCESS && error < TOTAL_ERRORS) {
        printf("Failed with error: %s\n", cbproErrorMsg[error]);
    }
}
