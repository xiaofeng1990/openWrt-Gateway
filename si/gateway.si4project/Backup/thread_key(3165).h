#ifndef _THREAD_KEY_H
#define _THREAD_KEY_H
#include <stdio.h>
#include "gw_config.h"

void *key_thread_f(void *parameter);
void key_thread_init(tGatewayInfo *gatewayInfo);
void key_thread_wait(tGatewayInfo *gatewayInfo);

#endif /* _THREAD_KEY_H */


