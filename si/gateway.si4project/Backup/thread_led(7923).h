#ifndef _THREAD_LED_H
#define _THREAD_LED_H
#include <stdio.h>
#include "gw_config.h"

void *led_thread_f(void *parameter);
void led_thread_init(tGatewayInfo *gatewayInfo);
void led_thread_wait(tGatewayInfo *gatewayInfo);

#endif /* _THREAD_LED_H */

