#include <stdio.h>

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "thread_report.h"
#include "debug.h"


void *report_thread_f(void *parameter)
{
	DEBUG_LOG("report thread: I'm report thread\n");

	/* 线程自销毁，当线程销毁时，自动回收资源 */
	pthread_detach(pthread_self());	
	struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;
	while(1)
	{
		DEBUG_LOG("report thread is run\n");
		sleep(5);
	}
	pthread_exit(0);
}

int report_thread_init(struct tGatewayInfo *gatewayInfo)
{
	int temp;

	/* 从数据库加载设备列表 */
	/*创建线程*/
	temp = pthread_create(&gatewayInfo->thread.report, NULL, report_thread_f, (void *)gatewayInfo);
	if(temp != 0)     
		DEBUG_LOG("report thread is err!\n");
	else
		DEBUG_LOG("report thread is ok\n");
		
	return temp;
}

void report_thread_wait(struct tGatewayInfo *gatewayInfo)
{
	/*等待线程结束*/
	if(gatewayInfo->thread.report !=0)
	{ 
		pthread_join(gatewayInfo->thread.report,NULL);
		DEBUG_LOG("report thread is over\n");
	}
}





