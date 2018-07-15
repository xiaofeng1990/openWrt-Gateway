#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <sys/time.h>
#include <string.h>
#include "usart.h"
#include "thread_usart_send.h"
#include "debug.h"
#include "gw_ipc.h"
#include "usart.h"
#include "gw_config.h"

void *usart_send_thread_f(void *parameter)
{
	char send_buff[USART_BUFF_LEN];
	mqd_t ret;
	unsigned int prio;
	size_t size;
	struct mq_attr attr;
	
	DEBUG_LOG("usart send thread ok\n");
	pthread_detach(pthread_self());
	struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;
	mq_getattr(gatewayInfo->mqueue.mqid_usart_s, &attr);
	size = attr.mq_msgsize;
	//DEBUG_LOG("flag=%ld max #msg=%ld max #bytes/msg=%ld #currently on queue=%ld\n", attr.mq_flags ,attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
	while(1)
	{
		memset(send_buff, 0, USART_BUFF_LEN);
		ret = mq_receive(gatewayInfo->mqueue.mqid_usart_s, (char*)send_buff, size, &prio);
		
		if(ret > 0)
		{
			DEBUG_LOG("usart wait data ok mq receice data len = %d\n", ret);
			if(uart_send(gatewayInfo->usart_fd , send_buff, USART_BUFF_LEN)>0)
				DEBUG_LOG("usart send data ok \n");
			else
				DEBUG_LOG("usart send data error\n");
		}
	}
	pthread_exit(0);
}

int usart_send_thread_init(struct tGatewayInfo *gatewayInfo)
{
	int temp;
	
	/*创建线程*/
	temp = pthread_create(&gatewayInfo->thread.usart_send, NULL, usart_send_thread_f, (void *)gatewayInfo);
	if(temp != 0)     
		DEBUG_LOG("usart send thread is err!\n");
	else
		DEBUG_LOG("usart send thread is ok\n");

	return temp;
}

void usart_send_thread_wait(struct tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.usart_send !=0)
	{ 
		pthread_join(gatewayInfo->thread.usart_send,NULL);
		DEBUG_LOG("usart send thread is over/n");
	}
}




