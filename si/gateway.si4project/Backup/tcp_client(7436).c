#include <stdio.h>
#include <stdint.h>
#include <strings.h>    
#include <unistd.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
//#include <linux/in.h>    
#include <stdlib.h>    
#include <memory.h>    
#include <arpa/inet.h>    
#include <netinet/in.h>    
	
#include <signal.h> //添加信号处理  防止向已断开的连接通信    

#include "tcp_client.h"
#include "debug.h"


/* 
 *允许用户使用三个tcp连接
 *0 mqtt  1 ota, 2 app 
 */
static int tcp_socket[3];		

/******************************************************************************
 * @fn      tcp_client_connect
 *
 * @brief   用户tcp连接接口
 *
 * @param   ip：服务器ip地址(char)
 *			port:端口号		
 *			socket_num: socket编号
 *
 * @return  0 TCP connect success ,other is error
 *****************************************************************************/
int tcp_client_connect(char* ip, int port,int socket_num)
{
	int ret = 0;
	int connect_number = 0;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	tcp_socket[socket_num] = -1;
	signal(SIGPIPE, SIG_IGN);
	
	do{
		tcp_socket[socket_num] = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(tcp_socket[socket_num]<0)
		{
			DEBUG_LOG("create socket error\n");
			return -1;
		}
		ret = connect(tcp_socket[socket_num], (struct sockaddr *)&addr, sizeof(addr));
		if(ret == 0)
		{
			DEBUG_LOG("sockte connect success [%d]\n", ret);
		}
		else
		{
			connect_number++;
			DEBUG_LOG("sockte connect error [%d] connect number %d\n", ret, connect_number);
			close(tcp_socket[socket_num]);
		}
	}while((ret!=0)&&(connect_number<3));
	if(connect_number>=3)
	{
		DEBUG_LOG("******sockte connect error *******\n");
		close(tcp_socket[socket_num]);
		return -1;
	}
	
	return 0;
}

 

int tcp_client_send(uint8_t *SendBuff, int lenght, int socketNum)
{
	return write(tcp_socket[socketNum],SendBuff,lenght);
}


int tcp_client_revc(uint8_t *buff, int lenght, int socketNum)
{
	return recv(tcp_socket[socketNum],buff,lenght, 0);
	
}
 
int tcp_client_close(int socketNum)
{
	//关闭套接字
	return close(tcp_socket[socketNum]);
}

int get_socket_number(int number)
{
	return tcp_socket[number];
}	

