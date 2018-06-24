#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <sys/time.h>
#include <string.h>
#include "usart.h"
#include "thread_usart_rceive.h"
#include "debug.h"
#include "gw_ipc.h"

static pthread_t usart_rcev_thread;

void *usart_rcev_thread_f()
{
	char rcev_buff[USART_BUFF_LEN];
	int ret;
	DEBUG_LOG("usart rcev thread ok\n");
	pthread_detach(pthread_self());
	
	while(1)
	{
		/* 阻塞读取串口消息 */
		memset(rcev_buff, 0, USART_BUFF_LEN);
		DEBUG_LOG("usart reading  data\n");
		ret = read(serial_fd, rcev_buff, USART_BUFF_LEN);  
		DEBUG_LOG("usart read data return len = %d\n", ret);  

		if(ret>0)
		{
			/* 向串口接收队列中发送消息 */
			if(mq_send(g_mqid_usart_r, (const char*)&rcev_buff, USART_BUFF_LEN, 1)==0)
				DEBUG_LOG("usart rcev thread send mq ok\n");
			else
				DEBUG_LOG("usart rcev thread send mq error\n");
		}
		
		
		sleep(4);
	}
	pthread_exit(0);
}

void usart_rcev_thread_create(void)
{
	int temp;
	memset(&usart_rcev_thread, 0, sizeof(pthread_t)); 
	/*创建线程*/
	if((temp = pthread_create(&usart_rcev_thread, NULL, usart_rcev_thread_f, NULL)) != 0)     
		DEBUG_LOG("usart rceive thread is err!\n");
	else
		DEBUG_LOG("usart rceive thread is ok\n");
}

void usart_rcev_thread_wait(void)
{
	/*等待线程结束*/
	if(usart_rcev_thread !=0)
	{ 
		pthread_join(usart_rcev_thread,NULL);
		DEBUG_LOG("usart rceive thread is over/n");
	}
}



