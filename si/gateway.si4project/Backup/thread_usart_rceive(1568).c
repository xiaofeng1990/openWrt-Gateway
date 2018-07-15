#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <sys/time.h>
#include <string.h>
#include "usart.h"
#include "thread_usart_rceive.h"
#include "debug.h"
#include "gw_ipc.h"


void *usart_rcev_thread_f(void *parameter)
{
	char rcev_buff[USART_BUFF_LEN];
	int ret;
	DEBUG_LOG("usart rcev thread ok\n");
	pthread_detach(pthread_self());
	struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;
	while(1)
	{
		/* 阻塞读取串口消息 */
		memset(rcev_buff, 0, USART_BUFF_LEN);
		ret = read(gatewayInfo->usart_fd, rcev_buff, USART_BUFF_LEN);  
		DEBUG_LOG("usart read data return len = %d\n", ret);  

		if(ret>0)
		{
			/* 向串口接收队列中发送消息 */
			if(mq_send(gatewayInfo->mqueue.mqid_usart_r, (const char*)&rcev_buff, USART_BUFF_LEN, 1)==0)
				DEBUG_LOG("usart rcev thread send mq ok\n");
			else
				DEBUG_LOG("usart rcev thread send mq error\n");
		}
	}
	pthread_exit(0);
}

int usart_rcev_thread_init(struct tGatewayInfo *gatewayInfo)
{
	int temp;

	/*创建线程*/
	temp = pthread_create(&gatewayInfo->thread.usart_rcev, NULL, usart_rcev_thread_f, (void *)gatewayInfo);
	if(temp != 0)     
		DEBUG_LOG("usart rceive thread is err!\n");
	else
		DEBUG_LOG("usart rceive thread is ok\n");

	return temp;
}

void usart_rcev_thread_wait(struct tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.usart_rcev)
	{ 
		pthread_join(gatewayInfo->thread.usart_rcev,NULL);
		DEBUG_LOG("usart rceive thread is over/n");
	}
}



