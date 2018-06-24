
#ifndef _GW_DATA_CONFIG_H
#define _GW_DATA_CONFIG_H
#include <stdio.h>
#include <pthread.h>

/* Application parameter*/
#define SERVER_IP_LENGTH			32
#define SERVER_DOMAIN_LENGTH		64
#define LOCAL_HW_MAC_LENGTH			16

typedef struct
{
	uint8_t		use_ip;	
	char		server_ip[SERVER_IP_LENGTH];
	char		domain[SERVER_DOMAIN_LENGTH];
	uint32_t	port;

	char        local_ip[SERVER_IP_LENGTH];
	uint32_t	local_port;
}s_ip_info;

typedef struct
{
	pthread_t	led;
	pthread_t	key;
	pthread_t	mqtt;
	pthread_t	ota;
	pthread_t	ping;
	pthread_t	report;
	pthread_t	scenes_manager;
	pthread_t	timers_manager;
	pthread_t	usart_rcev;
	pthread_t	usart_send;
	pthread_t	device_manager;
}thread_manage_s;

typedef struct
{
	mqd_t g_mqid_usart_r;		/* 串口接收队列 */
	mqd_t g_mqid_usart_s;		/* 串口发送队列 */
	mqd_t g_mqid_socket;		/* socket发送队列 */
}mq_manage_s;


typedef	struct
{
	thread_manage_s		thread;
	mq_manage_s			mqueue;
	char				mac[LOCAL_HW_MAC_LENGTH];
	
	tServer				server;	
}gw_info_s;


#endif	/* _GW_DATA_CONFIG_H */

