#include "condition.h"
#include "gw_ipc.h"
#include "debug.h"


/************************************** 条件变量 **************************************/
/* 串口回复条件变量结构体，包含所有回复条件 */

int ipc_init(struct tGatewayInfo *gatewayInfo)
{

	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 512;

	/* 互斥量初始化 */
	pthread_mutex_init(&(gatewayInfo->mysql.mutex_mysql), NULL);
	
	/* 条件变量初始化 */

	/* 队列初始化 可读可写，默认阻塞读 如果要设置为非阻塞读，就设置 O_NONBLOCK flag*/
	gatewayInfo->mqueue.mqid_usart_s = mq_open(MQ_USART_SEND, O_CREAT | O_RDWR, 0666, &attr);
	if (gatewayInfo->mqueue.mqid_usart_s == (mqd_t)-1)
	{
		goto err1;
	}	

	gatewayInfo->mqueue.mqid_usart_r = mq_open(MQ_USART_RECV, O_CREAT | O_RDWR, 0666, &attr);
	if (gatewayInfo->mqueue.mqid_usart_r == (mqd_t)-1)
	{
		goto err1;
	}

	gatewayInfo->mqueue.mqid_report = mq_open(MQ_REPORT, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_report == (mqd_t)-1)
	{
		goto err1;
	}

	gatewayInfo->mqueue.mqid_device = mq_open(MQ_DEVICE, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_device == (mqd_t)-1)
	{
		goto err1;
	}
	
	gatewayInfo->mqueue.mqid_scene = mq_open(MQ_SCENE, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_scene == (mqd_t)-1)
	{
		goto err1;
	}

	gatewayInfo->mqueue.mqid_timer = mq_open(MQ_TIMER, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_timer == (mqd_t)-1)
	{
		goto err1;
	}

	gatewayInfo->mqueue.mqid_execute = mq_open(MQ_EXECUTE, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_timer == (mqd_t)-1)
	{
		goto err1;
	}

	return 0;
	
err1:

	DEBUG_LOG("************pic init error***************\n");
	return -1;
}
