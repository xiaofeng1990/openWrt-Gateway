#ifndef __THREAD_USART_RCEV_H_
#define __THREAD_USART_RCEV_H_
#include <stdio.h>
#include "gw_config.h"

void *usart_rcev_thread_f(void *parameter);
int usart_rcev_thread_init(struct tGatewayInfo *gatewayInfo);
void usart_rcev_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_USART_RCEV_H_ */



