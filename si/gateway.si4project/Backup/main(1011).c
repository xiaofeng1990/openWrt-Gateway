#include <stdio.h>
#include "thread_led.h"
#include <pthread.h>
#include "thread_key.h"
#include "thread_mqtt.h"

int main()
{
	//led_thread_create();
	//key_thread_create();
	mqtt_thread_create();
	
	//key_thread_wait();
	mqtt_thread_wait();
	//led_thread_wait();
	return 0;
}