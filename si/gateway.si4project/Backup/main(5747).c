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
#include "gw_config.h"

struct tGatewayInfo g_gateway_info;

int main()
{
	int ret = 0;
	
	cJSON_InitHooks(NULL);
	ipc_init(&g_gateway_info);
	ret = open_usart(&g_gateway_info);		/* 串口初始化 */
	if(ret != 0)
		DEBUG_LOG("usart init error\n");
	led_thread_init(&g_gateway_info);
	key_thread_init(&g_gateway_info);
	mqtt_thread_init(&g_gateway_info);
	usart_rcev_thread_init(&g_gateway_info);
	usart_rcev_thread_init(&g_gateway_info);
	
	key_thread_wait(&g_gateway_info);
	mqtt_thread_wait(&g_gateway_info);
	led_thread_wait(&g_gateway_info);
	
	return 0;
}