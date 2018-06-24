#ifndef _THREAD_LED_H
#define _THREAD_LED_H
#include <stdio.h>
#include "gw_config.h"

void *led_thread_f(void *parameter);
void led_thread_init(struct tGatewayInfo *gatewayInfo);
void led_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* _THREAD_LED_H */

