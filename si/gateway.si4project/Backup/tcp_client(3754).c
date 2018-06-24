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
	
#include <signal.h> //添加信号处理  防止向已断开的连接通信    

#include "tcp.h"


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
 * @return  NULL
 *****************************************************************************/
int tcp_client_connect(char* ip, int port,int socket_num)
{
	int ret = 0;
	int connect_number = 0;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = PP_HTONS(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	tcp_socket[socket_num] = -1;
	
	do{
		tcp_socket[socket_num] = socket(AF_INET, SOCK_STREAM, 0);
		ret = connect(tcp_socket[socket_num], (struct sockaddr *)&addr, sizeof(addr));
		if(ret == 0)
		{
			rt_kprintf("sockte connect success [%d]\r\n", ret);
		}
		else
		{
			connect_number++;
			rt_kprintf("sockte connect error [%d] connect number %d\r\n", ret, connect_number);
			lwip_close(tcp_socket[socket_num]);
		}
	}while((ret!=0)&&(connect_number<3));
	if(connect_number>=3)
	{
		rt_kprintf("******sockte connect error *******\r\n");
		return 1;
	}
	
	return 0;
}

 

int tcp_client_send(uint8_t *SendBuff, int lenght, int socketNum)
{
	return lwip_write(tcp_socket[socketNum],SendBuff,lenght);
}


int tcp_client_revc(uint8_t *buff, int lenght, int socketNum)
{
	return lwip_read(tcp_socket[socketNum],buff,lenght);
	
}
 

int tcp_client_close(int socketNum)
{
	//关闭套接字
	return lwip_close(tcp_socket[socketNum]);
}

int get_socket_number(int number)
{
	return tcp_socket[number];
}	

