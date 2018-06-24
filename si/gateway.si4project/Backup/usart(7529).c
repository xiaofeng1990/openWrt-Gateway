
#include <stdio.h>    //标准输入输出定义  
#include <stdlib.h>   //标准函数库定义  
#include <unistd.h>   //Unix标准函数定义  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>    //文件控制定义  
#include <termios.h>  //POSIX中断控制定义  
#include <errno.h>    //错误号定义  
#include <string.h>
#include "debug.h"
#include "usart.h"

#define USART_DEVICE "/dev/ttyS1"

/* 串口文件描述符 */
int serial_fd = 0;
//打开串口并初始化设置  
int open_usart(void)  
{  
    serial_fd = open(USART_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);  
    if (serial_fd < 0) {  
        perror("open error");  
        return -1;  
    }  
      
    //串口主要设置结构体termios <termios.h>  
    struct termios options;  
      
    /**1. tcgetattr函数用于获取与终端相关的参数。 
    *参数fd为终端的文件描述符，返回的结果保存在termios结构体中 
    */  
    tcgetattr(serial_fd, &options);  
    /**2. 修改所获得的参数*/  
    options.c_cflag |= (CLOCAL | CREAD);	//设置控制模式状态，本地连接，接收使能  
    options.c_cflag &= ~CSIZE;				//字符长度，设置数据位之前一定要屏掉这个位  
    options.c_cflag &= ~CRTSCTS;			//无硬件流控  
    options.c_cflag |= CS8;					//8位数据长度  
    options.c_cflag &= ~CSTOPB;				//1位停止位  
    options.c_iflag |= IGNPAR;				//无奇偶检验位  
    options.c_oflag = 0; 					//输出模式  
    options.c_lflag = 0; 					//不激活终端模式  
    cfsetospeed(&options, B9600);			//设置波特率  
      
    /**3. 设置新属性，TCSANOW：所有改变立即生效*/  
    tcflush(serial_fd, TCIFLUSH);			//溢出数据可以接收，但不读  
    tcsetattr(serial_fd, TCSANOW, &options);  

	/* 设置串口为阻塞模式 */
    if(fcntl(serial_fd,F_SETFL,0)<0)
		DEBUG_LOG("usart set block error\n");
	
    return 0;  
}

/* 3.read usart data */
int uart_recv(int fd, char *data, int datalen)  
{  
    int len=0, ret = 0;  
    fd_set fs_read;  
    struct timeval tv_timeout;  
      
    FD_ZERO(&fs_read);  
    FD_SET(fd, &fs_read);  
    tv_timeout.tv_sec  = 1;  
    tv_timeout.tv_usec = 0;  
      
    ret = select(fd+1, &fs_read, NULL, NULL, &tv_timeout);  
    DEBUG_LOG("ret = %d\n", ret);  
    //如果返回0，代表在描述符状态改变前已超过timeout时间,错误返回-1  
         
    if (FD_ISSET(fd, &fs_read)) 
	{  
        len = read(fd, data, datalen);  
        DEBUG_LOG("len = %d\n", len);  
        return len;  
    } else 
	{  
        perror("select");  
        return -1;  
    }  
      
    return 0;  
} 

/* 4。send usart data */
int uart_send(int fd, char *data, int datalen)  
{  
    int len = 0;  
    len = write(fd, data, datalen);//实际写入的长度  
    if(len == datalen)
	{  
        return len;  
    }
	else 
	{  
        tcflush(fd, TCOFLUSH);//TCOFLUSH刷新写入的数据但不传送  
        return -1;  
    }  
      
    return 0;  
}  


