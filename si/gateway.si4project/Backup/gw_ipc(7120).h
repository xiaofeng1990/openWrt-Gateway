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


/* usart句柄互斥量 */
extern pthread_mutex_t g_mutex_usart;

/* socket句柄互斥量 */
extern pthread_mutex_t g_mutex_socket;
void ipc_init(struct tGatewayInfo *gatewayInfo);
#endif /* _GW_IPC_H_ */

