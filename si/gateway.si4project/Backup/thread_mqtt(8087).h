#ifndef _THREAD_MQTT_H
#define _THREAD_MQTT_H
#include <stdio.h>
#include "gw_config.h"

void *mqtt_thread_f(void *parameter);
void mqtt_thread_init(tGatewayInfo *gatewayInfo);
void mqtt_thread_wait(tGatewayInfo *gatewayInfo);


#endif /* _THREAD_MQTT_H */

