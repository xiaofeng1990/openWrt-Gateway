
#ifndef __GW_DATA_CONFIG_H_
#define __GW_DATA_CONFIG_H_

#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 

#include <pthread.h>
#include <stdint.h>
#include <mqueue.h>
 
#include <mysql/mysql.h> 
#include "mysql_client.h"
#include "cJSON.h"

/* Application parameter*/
#define IP_LENGTH			16			/* ip地址长度 */
#define DOMAIN_LENGTH		64			/* 域名地址长度 */
#define MAC_LENGTH			16			/* 网关mac地址长度 */
#define EIT_NAME			"eth0.1" 	/* 网关网卡名 */

#define DEV_MAC_LEN			8
#define FSN_TIME_OUT		10

//0x01 -- 0x50为功能扩展api   0x55 -- 0xXX 为控制命令api
enum eApiType{
	GW_PING = 0x0B,				//网关心跳
	GW_OTA,						//网关OTA的api
	
	GW_GET_TIME = 0X55,			//网关获取时间api
	GW_AUTHENTICATION, 			//网关向服务器认证
	
	SERVER_ADD_DEV = 201,		//添加子设备	
	SERVER_REQ_DEV_LIST,		//服务器请求设备列表
	SERVER_CONTROL_DEV,			//服务器控制子设备
	SERVER_ON_LINE,				//子设备上线
	SERVER_DEL_DEV,				//删除子设备
	SERVER_EDITOR_DEV,			//编辑子设备属性
	SERVER_EDITOR_DEFAULT_STATE,//编辑子设备默认状态
	SERVER_FIND_DEV,			//服务器查询单个子设备详情
	
	SERVER_ADD_SCENE = 300,		//服务器向网关发送添加场景
	SERVER_DEL_SCENE,			//删除场景
	SERVER_REQ_SCENE_LIST,		//请求场景列表
	SERVER_SCENE_DETAILS,		//请求场景详情
	SERVER_EXECUTE_SCENE,		//web或app执行情景
	SERVER_EDITOR_SCENE,		//编辑场景
	
	SERVER_ADD_TIMER = 400,		//服务器向网关发送添加定时
	SERVER_DEL_TIMER,			//删除定时
	SERVER_REQ_TIMER_LIST,		//请求定时列表
	SERVER_TIMER_DETAILS,		//请求定时详情
	GW_EXECUTE_TIMER,			//网关上报执行定时结果
	SERVER_EDITOR_TIMER,		//编辑定时
	SERVER_ON_OFF_TIMER,		//启动或者关闭定时
	
	SERVER_FIND_LOG_DATE = 601,		//服务器请求可查询日志日期
	SERVER_FIND_LOG,				//服务器查询日志
	SERVER_REQ_BACKUPS_LOG,			//网关向服务器发送请求备份日志
	SERVER_SERVER_GET_LOG_BACKUPS,	//服务器向网关获取备份日志
	SERVER_REP_SUB_DEV_LOG,			//向服务器紧急推送子设备错误信息	
};

enum eMsgSource{
	MSG_CON_TIMER =101,		/* 定时器控制子设备 */
	MSG_CON_WEB,			/* web或app控制子设备，情境 */
	MSG_CON_DEV_TRI,		/* 子设备触发联动控制场景,数据从串口得到 */

	MSG_REP_USART = 201,	/* 串口数据上报 */
	MSG_REP_WEB,			/* web或app请求上报数据 */
	MSG_REP_PING,			/* 网关上报心跳 */
	
	MSG_EDIT_WEB = 301,		/* web或app下发编辑指令添加，删除编辑设备，场景，定时，联动 */
	MSG_EDIT_USART,			/* 串口上报编辑指令，添加设备，删除设备 */
};

#define Check_Device_API(api)	((api == SERVER_ADD_DEV)				\
								||(api == SERVER_DEL_DEV)				\
								||(api == SERVER_EDITOR_DEV)			\
								||(api == SERVER_EDITOR_DEFAULT_STATE))

#define Check_Scene_API(api)	((api == SERVER_ADD_SCENE)		\
								||(api == SERVER_DEL_SCENE)		\
								||(api == SERVER_EDITOR_SCENE))


#define Check_Timer_API(api)	((api == SERVER_ADD_TIMER)		\
								||(api == SERVER_DEL_TIMER)		\
								||(api == SERVER_EDITOR_TIMER)	\
								||(api == SERVER_ON_OFF_TIMER))
								
#define Check_Report_API(api)	((api == SERVER_REQ_DEV_LIST)		\
								||(api == SERVER_FIND_DEV)			\
								||(api == SERVER_REQ_SCENE_LIST)	\
								||(api == SERVER_SCENE_DETAILS)		\
								||(api == SERVER_REQ_TIMER_LIST)	\
								||(api == SERVER_TIMER_DETAILS))

#define Check_Execute_API(api)	((api == SERVER_CONTROL_DEV)	\
								||(api == SERVER_EXECUTE_SCENE))

/* 设备属性信息 */
struct tDeviceInfo{
	char name[16];
	uint16_t type;
	uint8_t  mac[DEV_MAC_LEN];
	uint32_t zone;
	uint8_t  icon;
	uint32_t user;
	uint32_t ping_time;		/* 子设备向网关发送最近的一次心跳时间 */
	char data[40];			/* 子设备的私有数据 */
	struct tDeviceInfo *next;
};

/* 服务器和本地网卡信息 */
struct tNetworkInfo{
	char		server_ip[IP_LENGTH];		/* 服务器ip */
	char		domain[DOMAIN_LENGTH];		/* 服务器域名 */
	uint32_t	port;						/* 服务器端口 */

	char        local_ip[IP_LENGTH];		/* 网关本地ip */
	uint32_t	local_port;					/* 网关本地端口 */
	char		local_mac[MAC_LENGTH];		/* 网关本地mac */
};

/* 任务结构体 */
struct tThreads{
	pthread_t	led;
	pthread_t	key;
	pthread_t	mqtt;
	pthread_t	ota;
	pthread_t	ping;
	pthread_t	report;
	pthread_t	execute;
	pthread_t	scenes;
	pthread_t	timers;
	pthread_t	devices;
	pthread_t	usart_rcev;
	pthread_t	usart_send;
	pthread_t   usart_handle;
};

/* 队列结构体 */
struct tMessageQueue{
	mqd_t mqid_usart_r;		/* 串口接收队列 */
	mqd_t mqid_usart_s;		/* 串口发送队列 */
	mqd_t mqid_report;		/* report发送队列 */
	
	mqd_t mqid_execute;		/* 3.控制队列 */
	mqd_t mqid_device;		/* 4.子设备管理队列 */
	mqd_t mqid_scene;		/* 5.情境管理队列 */
	mqd_t mqid_timer;		/* 6.定时管理队列 */
	/* 7.联动管理队列       */
};


/* 队列消息结构体 */
struct tMsgData{
	char source;
	char data[512];
};

/* 操作数据库互斥量和mysql句柄 */
struct tMysqlInfo{
	/* 操作mysql句柄互斥量 */
	pthread_mutex_t mutex_mysql;
	MYSQL db;
};

/* 网关参数结构体 */
struct tGatewayInfo{
	int 					usart_fd;	/* 串口文件描述符 */
	struct tThreads			thread;
	struct tMessageQueue	mqueue;
	
	struct tNetworkInfo		network;
	struct tMysqlInfo		mysql;
	
	struct tDeviceInfo		*dev_list;	/* 子设备列表头 */
	//定时链表
	//情境链表
	//联动链表
	
};


extern struct tGatewayInfo g_gateway_info;


#endif	/* __GW_DATA_CONFIG_H_ */

