#include <stdio.h>

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "thread_scene.h"
#include "debug.h"


void *scene_thread_f(void *parameter)
{
	DEBUG_LOG("scene thread: I'm scene thread\n");

	/* 线程自销毁，当线程销毁时，自动回收资源 */
	pthread_detach(pthread_self());	
	struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;
	while(1)
	{
		DEBUG_LOG("scene thread is run\n");
		sleep(5);
	}
	pthread_exit(0);
}

int scene_thread_init(struct tGatewayInfo *gatewayInfo)
{
	int temp;

	/* 从数据库加载设备列表 */
	/*创建线程*/
	temp = pthread_create(&gatewayInfo->thread.scenes, NULL, scene_thread_f, (void *)gatewayInfo);
	if(temp != 0)     
		DEBUG_LOG("scene thread is err!\n");
	else
		DEBUG_LOG("scene thread is ok\n");
		
	return temp;
}

void scene_thread_wait(struct tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.scenes !=0)
	{ 
		pthread_join(gatewayInfo->thread.scenes,NULL);
		DEBUG_LOG("scene thread is over\n");
	}
}






