
#ifndef _GW_DATA_CONFIG_H
#define _GW_DATA_CONFIG_H
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <mqueue.h>

/* Application parameter*/
#define SERVER_IP_LENGTH			32
#define SERVER_DOMAIN_LENGTH		64
#define LOCAL_HW_MAC_LENGTH			16

struct tServerInfo{
	uint8_t		use_ip;	
	char		server_ip[SERVER_IP_LENGTH];
	char		domain[SERVER_DOMAIN_LENGTH];
	uint32_t	port;

	char        local_ip[SERVER_IP_LENGTH];
	uint32_t	local_port;
};

struct tThreads{
	pthread_t	led;
	pthread_t	key;
	pthread_t	mqtt;
	pthread_t	ota;
	pthread_t	ping;
	pthread_t	report;
	pthread_t	usart_rcev;
	pthread_t	usart_send;
	pthread_t	scenes_manager;
	pthread_t	timers_manager;
	pthread_t	device_manager;
};

struct tMessageQueue{
	mqd_t mqid_usart_r;		/* 串口接收队列 */
	mqd_t mqid_usart_s;		/* 串口发送队列 */
	mqd_t mqid_socket;		/* socket发送队列 */
	
	/* 3.控制队列 */
	/* 4.子设备管理队列 */
	/* 5.情境管理队列 */
	/* 6.定时管理队列 */
	/* 7.联动管理队列       */
};


struct tGatewayInfo{
	int 					usart_fd;	/* 串口文件描述符 */
	char					mac[LOCAL_HW_MAC_LENGTH];
	struct tThreads			thread;
	struct tMessageQueue	mqueue;
	
	struct tServerInfo		server;	
	//设备链表
	//定时链表
	//情境链表
	//联动链表
	
};


#endif	/* _GW_DATA_CONFIG_H */

