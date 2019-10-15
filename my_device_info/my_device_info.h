#ifndef _MY_DEVICE_INFO_H_
#define _MY_DEVICE_INFO_H_

#include "infra_defs.h"

extern char *device_ver;
extern char g_product_key[IOTX_PRODUCT_KEY_LEN + 1];
extern char g_product_secret[IOTX_PRODUCT_SECRET_LEN + 1];
extern char g_device_name[IOTX_DEVICE_NAME_LEN + 1];
extern char g_device_secret[IOTX_DEVICE_SECRET_LEN + 1];

int _ota_mqtt_client(void);

#endif


