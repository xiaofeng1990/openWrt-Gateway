#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <sys/time.h>
#include <string.h>
#include "thread_key.h"
#include "debug.h"



void *key_thread_f(void *parameter)
{
	DEBUG_LOG("key thread: I'm key thread\n");
	pthread_detach(pthread_self());
	//struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;
	while(1)
	{
		DEBUG_LOG("key thread is run\n");
		sleep(5);
	}
	pthread_exit(0);
}

int key_thread_init(struct tGatewayInfo *gatewayInfo)
{
	int temp;
	
	/*创建线程*/
	temp = pthread_create(&gatewayInfo->thread.key, NULL, key_thread_f, (void *)gatewayInfo);
	if(temp != 0)     
		DEBUG_LOG("key thread is err!\n");
	else
		DEBUG_LOG("key thread is ok\n");
		
	return temp;
}

void key_thread_wait(struct tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.key !=0)
	{ 
		pthread_join(gatewayInfo->thread.key,NULL);
		DEBUG_LOG("key thread is over/n");
	}
}


