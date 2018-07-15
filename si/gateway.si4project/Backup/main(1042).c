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
#include "thread_device.h"
#include "thread_execute.h"
#include "thread_report.h"
#include "thread_scene.h"
#include "thread_timer.h"

struct tGatewayInfo g_gateway_info;

int main()
{
	int ret = 0;

	memset(&g_gateway_info, 0, sizeof(struct tGatewayInfo));
	
	cJSON_InitHooks(NULL);
	ipc_init(&g_gateway_info);
	ret = open_usart(&g_gateway_info);		/* 串口初始化 */
	if(ret != 0)
		DEBUG_LOG("usart init error\n");
	//led_thread_init(&g_gateway_info);
	//key_thread_init(&g_gateway_info);

	ret = mqtt_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("mqtt_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}
	
	ret = usart_rcev_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("usart_rcev_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}
	
	ret = usart_rcev_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("usart_rcev_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}
	
	ret = dev_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("dev_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}
	
	ret = exe_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("exe_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}

	ret = report_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("report_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}

	ret = scene_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("scene_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}

	ret = timer_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			sleep(5);
			DEBUG_LOG("timer_thread_init failed ret = [%d] !!!!!\n", ret);
		}
	}
	
	key_thread_wait(&g_gateway_info);
	mqtt_thread_wait(&g_gateway_info);
	led_thread_wait(&g_gateway_info);
	
	return 0;
}