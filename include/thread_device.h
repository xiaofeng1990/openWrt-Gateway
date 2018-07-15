#ifndef __THREAD_DEVICE_H_
#define __THREAD_DEVICE_H_
#include <stdio.h>
#include "gw_config.h"

void *dev_thread_f(void *parameter);
int dev_thread_init(struct tGatewayInfo *gatewayInfo);
void dev_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_DEVICE_H_ */

