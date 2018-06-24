#include <stdio.h>
#include "thread_led.h"
#include <pthread.h>
#include "thread_key.h"

int main()
{
	led_thread_create();
	key_thread_create();
	while(1);
	return 0;
}