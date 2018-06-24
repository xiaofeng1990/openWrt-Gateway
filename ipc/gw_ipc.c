#include "condition.h"
#include "gw_ipc.h"
#include "debug.h"


#define MQ_USART_SEND	"/mq_usart_send"
#define MQ_SOCKET_SEND	"/mq_socket_send"
#define MQ_USART_RECV	"/mq_usart_recv"

/* 信号量 */

/************************************** 互斥量 **************************************/

/* socket句柄互斥量 */
pthread_mutex_t g_mutex_socket;


/************************************** 条件变量 **************************************/
/* 串口回复条件变量结构体，包含所有回复条件 */


void ipc_init(struct tGatewayInfo *gatewayInfo)
{
	/* 互斥量初始化 */
	

	pthread_mutex_init(&(gatewayInfo->mysql.mutex_mysql), NULL);
	pthread_mutex_init(&(gatewayInfo->fsn.fsn), NULL);
	
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 512;
	
	/* 条件变量初始化 */

	/* 队列初始化 可读可写，默认阻塞读 如果要设置为非阻塞读，就设置 O_NONBLOCK flag*/
	gatewayInfo->mqueue.mqid_usart_s = mq_open(MQ_USART_SEND, O_CREAT | O_RDWR, 0666, &attr);
	if (gatewayInfo->mqueue.mqid_usart_s == (mqd_t)-1)
		DEBUG_LOG("mq_open usart_s error\n");	
	else
		DEBUG_LOG("mq_open usart_s succ\n");

	gatewayInfo->mqueue.mqid_usart_r = mq_open(MQ_USART_RECV, O_CREAT | O_RDWR, 0666, &attr);
	if (gatewayInfo->mqueue.mqid_usart_r == (mqd_t)-1)
		DEBUG_LOG("mq_open usart_r error\n");	
	else
		DEBUG_LOG("mq_open usart_r succ\n");

	gatewayInfo->mqueue.mqid_socket = mq_open(MQ_SOCKET_SEND, O_CREAT | O_RDWR, 0666, NULL);
	if (gatewayInfo->mqueue.mqid_socket == (mqd_t)-1)
		DEBUG_LOG("mq_open socket error\n");	
	else
		DEBUG_LOG("mq_open socket succ\n");
	
}
