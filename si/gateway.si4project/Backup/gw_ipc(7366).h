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



/* 1.串口发送队列 */
extern mqd_t g_mqid_usart_s;
/* 8.串口接收队列 */
extern mqd_t g_mqid_usart_r;

/* 2.socket发送队列 */
extern mqd_t g_mqid_socket;

/* 3.控制队列 */
/* 4.子设备管理队列 */
/* 5.情境管理队列 */
/* 6.定时管理队列 */
/* 7.联动管理队列       */



/* usart句柄互斥量 */
extern pthread_mutex_t g_mutex_usart;

/* socket句柄互斥量 */
extern pthread_mutex_t g_mutex_socket;

void ipc_init(void);


#endif /* _GW_IPC_H_ */

