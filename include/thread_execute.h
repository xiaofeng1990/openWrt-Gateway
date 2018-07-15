#ifndef __THREAD_EXECUTE_H_
#define __THREAD_EXECUTE_H_
#include <stdio.h>
#include "gw_config.h"

void *exe_thread_f(void *parameter);
int exe_thread_init(struct tGatewayInfo *gatewayInfo);
void exe_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_EXECUTE_H_ */

