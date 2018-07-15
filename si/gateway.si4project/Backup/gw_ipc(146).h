#ifndef _GW_IPC_H_
#define _GW_IPC_H_

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "gw_config.h"

#define MQ_USART_SEND	"/mq_usart_send"
#define MQ_USART_RECV	"/mq_usart_recv"

#define MQ_REPORT		"/mq_report"
#define MQ_DEVICE		"/mq_device"
#define MQ_SCENE		"/mq_scene"
#define MQ_TIMER		"/mq_timer"
#define MQ_EXECUTE		"/mq_execute"


/* usart句柄互斥量 */
extern pthread_mutex_t g_mutex_usart;

/* socket句柄互斥量 */
extern pthread_mutex_t g_mutex_socket;
int ipc_init(struct tGatewayInfo *gatewayInfo);
#endif /* _GW_IPC_H_ */

