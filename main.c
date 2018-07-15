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
#include "thread_usart_handle.h"
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
	ret = ipc_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("ipc_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}
	ret = open_usart(&g_gateway_info);		/* 串口初始化 */
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("open_usart failed ret = [%d] !!!!!\n", ret);
			sleep(5);	
		}
	}
	//led_thread_init(&g_gateway_info);
	//key_thread_init(&g_gateway_info);

	ret = mqtt_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{	
			DEBUG_LOG("mqtt_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}
	
	ret = usart_rcev_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("usart_rcev_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}
	
	ret = usart_send_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("usart_send_thread_init failed ret = [%d] !!!!!\n", ret);		
			sleep(5);
		}
	}
	
	ret = dev_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("dev_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}
	
	ret = exe_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("exe_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}

	ret = report_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("report_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}

	ret = scene_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("scene_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}

	ret = timer_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("timer_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}

	ret = usart_handle_thread_init(&g_gateway_info);
	if(ret != 0)
	{
		while(1)
		{
			DEBUG_LOG("usart_handle_thread_init failed ret = [%d] !!!!!\n", ret);
			sleep(5);
		}
	}
	
	//led_thread_wait(&g_gateway_info);
	//key_thread_wait(&g_gateway_info);
	mqtt_thread_wait(&g_gateway_info);
	usart_rcev_thread_wait(&g_gateway_info);
	usart_send_thread_wait(&g_gateway_info);
	dev_thread_wait(&g_gateway_info);
	exe_thread_wait(&g_gateway_info);
	report_thread_wait(&g_gateway_info);
	scene_thread_wait(&g_gateway_info);
	timer_thread_wait(&g_gateway_info);
	usart_handle_thread_wait(&g_gateway_info);
	
	return 0;
}
