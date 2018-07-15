#ifndef __THREAD_KEY_H_
#define __THREAD_KEY_H_
#include <stdio.h>
#include "gw_config.h"

void *key_thread_f(void *parameter);
int key_thread_init(struct tGatewayInfo *gatewayInfo);
void key_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_KEY_H_ */


