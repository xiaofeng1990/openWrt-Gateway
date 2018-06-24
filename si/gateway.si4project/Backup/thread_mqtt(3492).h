#ifndef _THREAD_MQTT_H
#define _THREAD_MQTT_H
#include <stdio.h>

void *mqtt_thread_f();
void mqtt_thread_create(void);
void mqtt_thread_wait(void);


#endif /* _THREAD_MQTT_H */

