#ifndef __THREAD_LED_H_
#define __THREAD_LED_H_
#include <stdio.h>
#include "gw_config.h"

void *led_thread_f(void *parameter);
int led_thread_init(struct tGatewayInfo *gatewayInfo);
void led_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_LED_H_ */

