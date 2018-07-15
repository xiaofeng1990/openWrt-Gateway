#include <stdio.h>
#include <stdint.h>
#include <strings.h> 
#include <net/if.h>

#include <unistd.h> 
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#include <sys/types.h>    
#include <sys/socket.h>  
#include <fcntl.h>

//#include <linux/in.h>    
#include <stdlib.h>    
#include <memory.h>    
#include <arpa/inet.h>    
#include <netinet/in.h>    
#include <net/route.h>
#include <net/if_arp.h>
#include <signal.h> //添加信号处理  防止向已断开的连接通信    

#include "tcp_client.h"
#include "debug.h"
#include "gw_config.h"


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

int tcp_get_socket_fd(int number)
{
	return tcp_socket[number];
}

/******************************************************************************
 * @fn      tcp_get_eth_info
 *
 * @brief   获得网卡信息，ip地址，mac地址
 *
 * @param   gatewayInfo：网关信息结构体
 *			fd_num: socket句柄编号		
 *	
 * @return  -1 error  0 success
 *****************************************************************************/

int tcp_get_eth_info(struct tGatewayInfo *gatewayInfo, int fd_num)
{
	struct ifreq ifr;
	struct sockaddr_in *sin;
	
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, EIT_NAME);
	memset(&sin, 0, sizeof(sin));


	/* 获得网关IP */
	if(ioctl(tcp_socket[fd_num], SIOCGIFADDR, &ifr) != -1)
	{
		sin = (struct sockaddr_in *)&ifr.ifr_addr;
		strcpy(gatewayInfo->server.local_ip, inet_ntoa(sin->sin_addr));
		DEBUG_LOG("IP address is %s\n", gatewayInfo->server.local_ip);	
	}
	else
	{
		DEBUG_LOG("**********get ip error!!!**********\n");
		goto err1;
	}

	/* 获得网关mac地址 */
	if(ioctl(tcp_socket[fd_num], SIOCGIFHWADDR, &ifr) != -1)
	{
		sin = (struct sockaddr_in *)&ifr.ifr_hwaddr;
		sprintf(gatewayInfo->server.local_mac, "%02x%02x%02x%02x%02x%02x",
		(unsigned char)ifr.ifr_hwaddr.sa_data[0],
		(unsigned char)ifr.ifr_hwaddr.sa_data[1],
		(unsigned char)ifr.ifr_hwaddr.sa_data[2],
		(unsigned char)ifr.ifr_hwaddr.sa_data[3],
		(unsigned char)ifr.ifr_hwaddr.sa_data[4],
		(unsigned char)ifr.ifr_hwaddr.sa_data[5]);
		DEBUG_LOG("Mac address is %s\n", gatewayInfo->server.local_mac);
	}
	else
	{
		DEBUG_LOG("**********get mac error!!!**********\n");
		goto err1;
	}

	return 0;
	
err1:
 return -1;
}
