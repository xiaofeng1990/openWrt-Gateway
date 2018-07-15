#ifndef __THREAD_REPORT_H_
#define __THREAD_REPORT_H_
#include <stdio.h>
#include "gw_config.h"

void *report_thread_f(void *parameter);
int report_thread_init(struct tGatewayInfo *gatewayInfo);
void report_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_REPORT_H_ */


