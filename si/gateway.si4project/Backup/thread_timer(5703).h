#ifndef __THREAD_TIMER_H_
#define __THREAD_TIMER_H_
#include <stdio.h>
#include "gw_config.h"

void *timer_thread_f(void *parameter);
int timer_thread_init(struct tGatewayInfo *gatewayInfo);
void timer_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_TIMER_H_ */



