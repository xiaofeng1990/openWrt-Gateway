#ifndef _THREAD_LED_H
#define _THREAD_LED_H
#include <stdio.h>

static void *led_thread_f();
void led_thread_create(void);
void led_thread_wait(void);

#endif /* _THREAD_LED_H */

