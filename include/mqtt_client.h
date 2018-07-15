
#ifndef __MQTT_CLIENT_H
#define __MQTT_CLIENT_H
#include <stdio.h> 
#include <stdint.h>
#include <strings.h>  
#include "gw_config.h"


#define MQTT_PING_TIMER		10				//mqtt心跳时间，单位为秒

#define SOCK_TARGET_HOST  	"47.91.244.217"
#define SOCK_TARGET_IP		"www.basonplc.cn"
//#define SOCK_TARGET_HOST  	"118.89.159.225"
#define MQTT_PORT			1883			//MQTT端口

typedef struct topic{        
	char  type[6];       
	char  mac[16];     
	char  cmd[16];      
} mqtt_topic;

int mqtt_sendPacketBuffer(uint8_t* buf, int buflen);
int mqtt_getdata(uint8_t* buf, int count);
int mqtt_close(void);
int mqtt_connect(struct tGatewayInfo *gatewayInfo);

int mqtt_publish(char *pTopic, char *pMessage);
int mqtt_subscribe(char *pTopic);
mqtt_topic topic_analyze(char * topic,int Len);
int mqtt_ping_req(void);
int mqtt_get_api(char* json_data, int *api);

#endif	//__MQTT_CLIENT_H

