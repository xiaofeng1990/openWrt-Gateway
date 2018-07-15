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
	mqd_t ret;
	unsigned int prio;
	size_t size;
	struct mq_attr attr;
	struct tMsgData mq_data;
	
	DEBUG_LOG("report thread: I'm report thread\n");

	/* 线程自销毁，当线程销毁时，自动回收资源 */
	pthread_detach(pthread_self());	
	struct tGatewayInfo *gatewayInfo = (struct tGatewayInfo *)parameter;

	mq_getattr(gatewayInfo->mqueue.mqid_report, &attr);		/* 获得消息队列属性 */
	size = attr.mq_msgsize;									/* 获得消息队列属性中的单个消息大小属性 */

	DEBUG_LOG("*****************report message queues*********************\n");
	DEBUG_LOG("flag=%ld max #msg=%ld max #bytes/msg=%ld #currently on queue=%ld\n", attr.mq_flags ,attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	
	while(1)
	{
		memset(&mq_data, 0, sizeof(struct tMsgData));
		DEBUG_LOG("report thread wait message queue!!!!!\n");
		ret = mq_receive(gatewayInfo->mqueue.mqid_report, (char*)&mq_data, size, &prio);
		if(ret > 0)
		{
			DEBUG_LOG("report thread wait data ok mq receice data len = %d\n", ret);
		}	
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
		DEBUG_LOG("$$$$$$$$$$$$$$$$ report thread is over $$$$$$$$$$$$$$$$\n");
	}
}





