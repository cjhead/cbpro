#ifndef CBPRO_ERR_H
#define CBPRO_ERR_H

typedef enum cbproError_t {
    SUCCESS,
    FILE_NOT_FOUND,
    FAILED_MEMORY_ALLOCATION,
    NOT_AUTHORIZED,
    TOTAL_ERRORS
} CBPRO_ERROR;

void errorMsg(int error);

#endif
