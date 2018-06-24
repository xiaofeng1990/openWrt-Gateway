#ifndef _THREAD_USART_RCEV_H
#define _THREAD_USART_RCEV_H
#include <stdio.h>

void *usart_rcev_thread_f();
void usart_rcev_thread_create(void);
void usart_rcev_thread_wait(void);

#endif /* _THREAD_USART_RCEV_H */



