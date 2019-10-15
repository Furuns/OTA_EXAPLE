#ifndef __TCP_CLIENT_H_
#define __TCP_CLIENT_H_

#include "types.h"
#include "stdint.h"

void MQTT_CON_ALI(void);
void replace_string(char *result, char *source, char* s1, char *s2);
uint8_t OpenClientConnection(SOCKET fd, uint8_t type, const char* name, uint8_t* s_ip, uint16_t s_port, uint16_t l_port);
#endif

