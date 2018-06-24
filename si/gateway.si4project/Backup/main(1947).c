#include <stdio.h>
#include "thread_led.h"
#include <pthread.h>
#include "thread_key.h"
#include "thread_mqtt.h"
#include "usart.h"
#include "debug.h"

#include "gw_ipc.h"
#include "thread_usart_send.h"
#include "thread_usart_rceive.h"
int main()
{
	int ret = 0;

	ipc_init();
	ret = open_usart();		/* 串口初始化 */
	if(ret != 0)
		DEBUG_LOG("usart init error\n");
	//led_thread_create();
	//key_thread_create();
	mqtt_thread_create();
	usart_rcev_thread_create();
	usart_send_thread_create();
	//key_thread_wait();
	mqtt_thread_wait();
	//led_thread_wait();
	
	return 0;
}