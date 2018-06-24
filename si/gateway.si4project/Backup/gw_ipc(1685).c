#include "condition.h"
#include "gw_ipc.h"


#define MQ_USART_SEND	"/mq_usart_send"
#define MQ_SOCKET_SEND	"/mq_socket_send"
#define MQ_USART_RECV	"/mq_usart_recv"

/* 信号量 */

/************************************** 互斥量 **************************************/
/* usart句柄互斥量 */
pthread_mutex_t g_mutex_usart;

/* socket句柄互斥量 */
pthread_mutex_t g_mutex_socket;

/* 队列句柄互斥量 */

/************************************** 条件变量 **************************************/
/* 串口回复条件变量结构体，包含所有回复条件 */

/************************************** 队列 **************************************/
/* 1.串口发送队列 */
mqd_t g_mqid_usart_s;

/* 2.socket发送队列 */
mqd_t g_mqid_socket;

/* 3.控制队列 */
/* 4.子设备管理队列 */
/* 5.情境管理队列 */
/* 6.定时管理队列 */
/* 7.联动管理队列       */

/* 8.串口接收队列 */
mqd_t g_mqid_usart_r;

void ipc_init(void)
{
	/* 互斥量初始化 */
	pthread_mutex_init(&g_mutex_usart, NULL);
	pthread_mutex_init(&g_mutex_socket, NULL);
	
	/* 条件变量初始化 */

	/* 队列初始化 可读可写，默认阻塞读 如果要设置为非阻塞读，就设置 O_NONBLOCK flag*/

	
	g_mqid_usart_s = mq_open(MQ_USART_SEND, O_CREAT | O_RDWR, 0666, NULL);
	if (g_mqid_usart_s == (mqd_t)-1)
		printf("mq_open usart_s error\n");	
	else
		printf("mq_open usart_s succ\n");

	g_mqid_usart_r = mq_open(MQ_USART_RECV, O_CREAT | O_RDWR, 0666, NULL);
	if (g_mqid_usart_r == (mqd_t)-1)
		printf("mq_open usart_r error\n");	
	else
		printf("mq_open usart_r succ\n");

	g_mqid_socket = mq_open(MQ_SOCKET_SEND, O_CREAT | O_RDWR, 0666, NULL);
	if (g_mqid_socket == (mqd_t)-1)
		printf("mq_open socket error\n");	
	else
		printf("mq_open socket succ\n");
	
}
