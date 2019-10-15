#ifndef _HAL_TLS_MBEDTLS_H_
#define _HAL_TLS_MBEDTLS_H_

#include "stdint.h"

typedef enum {
  MY_TLS_STATUS_OK             = 0,
  MY_TLS_STATUS_ERROR          = 1,
  MY_TLS_STATUS_NOT_SUPPORTED  = 2,
  MY_TLS_STATUS_JOINED         = 3,                                    
  MY_TLS_STATUS_ASSIGNED       = 4,  
}MY_TLS_Status_t;

uintptr_t my_HAL_SSL_Establish(const char *host, uint16_t port, const char *ca_crt, uint32_t ca_crt_len);
int my_HAL_SSL_Read(uintptr_t handle, char *buf, int len, int timeout_ms);
int my_HAL_SSL_Write(uintptr_t handle, const char *buf, int len, int timeout_ms);
int32_t my_HAL_SSL_Destroy(uintptr_t handle);

#endif
