#ifndef __USART_HANDLE_TIMER_H_
#define __USART_HANDLE_TIMER_H_
#include <stdio.h>
#include "gw_config.h"

void *usart_handle_thread_f(void *parameter);
int usart_handle_thread_init(struct tGatewayInfo *gatewayInfo);
void usart_handle_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __USART_HANDLE_TIMER_H_ */


