
#ifndef __USART_
#define __USART_

#include <stdio.h> 
#include <stdint.h>
#include <strings.h> 
#include "gw_config.h"

#define	USART_BUFF_LEN	128

int open_usart(struct tGatewayInfo *gatewayInfo);
int uart_recv(int fd, char *data, int datalen);
int uart_send(int fd, char *data, int datalen);

#endif	//__USART_