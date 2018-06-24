/***************************************************************
 用户tcp接口
***************************************************************/

#ifndef _TCP_CLIENTH_
#define _TCP_CLIENTH_

#include <stdio.h>    
#include <strings.h>    
#include <unistd.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
//#include <linux/in.h>    
#include <stdlib.h>    
#include <memory.h>    
#include <arpa/inet.h>    
#include <netinet/in.h> 

/* 
 *允许用户使用三个tcp连接
 *0 mqtt  1 ota, 2 app 
 */
#define SOCKET_MQTT		0
#define SOCKET_OTA		1
#define SOCKET_APP		2

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

		
int tcp_client_connect(char* ip, int port,int socketNum);
int tcp_client_send(uint8_t * SendBuff, int lenght, int socketNum);
int tcp_client_revc(uint8_t * buff, int lenght, int socketNum);
int tcp_client_close(int socketNum);
int get_socket_number(int number);

#endif	//_TCP_CLIENTH_