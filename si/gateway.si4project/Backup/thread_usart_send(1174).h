#ifndef _THREAD_USART_SEND_H
#define _THREAD_USART_SEND_H
#include <stdio.h>

static void *usart_send_thread_f();
void usart_send_thread_create(void);
void usart_send_thread_wait(void);

#endif /* _THREAD_USART_SEND_H */




