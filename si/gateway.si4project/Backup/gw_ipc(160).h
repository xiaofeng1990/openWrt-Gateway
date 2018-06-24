#ifndef _GW_IPC_H_
#define _GW_IPC_H_

#include <pthread.h>

#define MQ_USART_SEND	"/mq_usart_send"
#define MQ_SOCKET_SEND	"/mq_socket_send"
#define MQ_USART_RECV	"/mq_usart_recv"


/* 1.串口发送队列 */
extern mqd_t g_mqid_usart_s;

/* 2.socket发送队列 */
extern mqd_t g_mqid_socket;

/* 3.控制队列 */
/* 4.子设备管理队列 */
/* 5.情境管理队列 */
/* 6.定时管理队列 */
/* 7.联动管理队列       */

/* 8.串口接收队列 */
extern mqd_t g_mqid_usart_r;

/* usart句柄互斥量 */
extern pthread_mutex_t g_mutex_usart;

/* socket句柄互斥量 */
extern pthread_mutex_t g_mutex_socket;

void ipc_init(void);


#endif /* _GW_IPC_H_ */

