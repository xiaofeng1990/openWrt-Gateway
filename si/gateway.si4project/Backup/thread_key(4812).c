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
	tGatewayInfo *gatewayInfo = (tGatewayInfo *)parameter;
	while(1)
	{
		printf("key thread is run\n");
		sleep(5);
	}
	pthread_exit(0);
}

void key_thread_init(tGatewayInfo *gatewayInfo)
{
	int temp;
	/*创建线程*/
	if((temp = pthread_create(&gatewayInfo->thread.key, NULL, key_thread_f, (void *)gatewayInfo)) != 0)     
		DEBUG_LOG("key thread is err!\n");
	else
		DEBUG_LOG("key thread is ok\n");

}

void key_thread_wait(tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.key !=0)
	{ 
		pthread_join(gatewayInfo->thread.key,NULL);
		DEBUG_LOG("key thread is over/n");
	}
}


