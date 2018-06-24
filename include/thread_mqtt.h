#ifndef __THREAD_MQTT_H_
#define __THREAD_MQTT_H_
#include <stdio.h>
#include "gw_config.h"

void *mqtt_thread_f(void *parameter);
void mqtt_thread_init(struct tGatewayInfo *gatewayInfo);
void mqtt_thread_wait(struct tGatewayInfo *gatewayInfo);


#endif /* __THREAD_MQTT_H_ */

