#ifndef _THREAD_USART_SEND_H
#define _THREAD_USART_SEND_H
#include <stdio.h>
#include "gw_config.h"

void *usart_send_thread_f(void *parameter);
void usart_send_thread_init(struct tGatewayInfo *gatewayInfo);
void usart_send_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* _THREAD_USART_SEND_H */




