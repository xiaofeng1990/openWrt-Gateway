
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mqtt.h"
#include "tcp_client.h"
#include "mqtt/MQTTPacket.h"
   
#include <unistd.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
   
#include <memory.h>    
#include <arpa/inet.h>    
#include <netinet/in.h> 
#include <netdb.h>


#define MQTT_PACKET_SIZE_MAX  2048

/******************************************************************************
 * @fn      transport_sendPacketBuffer
 *
 * @brief  	MQTT通过TCP的socket发送数据 
 *
 * @param   buf:发送数据缓存	buflen:发送数据长度		
 *			s:socket句柄，凭借句柄操作打开的socket
 * @return  -1：发送失败	ERR_OK：发送成功
 *****************************************************************************/
int mqtt_sendPacketBuffer(uint8_t* buf, int buflen)
{
	int ret = 0;
	ret = tcp_client_send(buf, buflen,SOCKET_MQTT);
	
	return ret;
}

/* 2.通过TCP接收数据 */
/******************************************************************************
 * @fn      transport_getdata
 *
 * @brief  	MQTT通过TCP的socket接收函数
 *
 * @param   buf:接收数据缓存	count:接收数据长度	
 *			s:socket句柄，凭借句柄操作打开的socket
 * @return  -1：发送失败		>0：表示接收成功，返回接收到的数据长度
 *****************************************************************************/
int mqtt_getdata(uint8_t* buf, int count)
{
	int ret = 0;

	ret = tcp_client_revc(buf, count, SOCKET_MQTT);
	
	return ret;
}


/* 4.关闭socket */
/******************************************************************************
 * @fn      transport_open
 *
 * @brief  	MQTT通过TCP关闭一个socket
 *
 * @param   NULL
 *
 * @return  0：成功
 *****************************************************************************/
int mqtt_close(void)
{
	tcp_client_close(SOCKET_MQTT);
	return 0;
}

/******************************************************************************
 * @fn      mqtt_connect
 *
 * @brief  	连接到mqtt服务器
 *
 * @param   
 *
 * @return  0：成功      -1：失败
 *****************************************************************************/
int mqtt_connect(void)
{
	uint32_t len;
	int ret;
	struct hostent *hptr;
	char ipbuf[32] = "";
	
	int dns_number = 0;
	uint8_t buf[MQTT_PACKET_SIZE_MAX];
	MQTTPacket_connectData	data = MQTTPacket_connectData_initializer;
	
	/* 域名解析 */
	do{
		hptr = gethostbyname(SOCK_TARGET_IP);
		if(hptr != NULL)
		{
			sprintf(ipbuf, "%s",inet_ntop(hptr->h_addrtype, hptr->h_addr, ipbuf, sizeof(ipbuf)));
			printf("dns ok ipbuf = %s\n", ipbuf);
		}
		else
		{
			dns_number++;
			printf("dns error %d\n", dns_number);
		}	
	}while((hptr==NULL)&&(dns_number<3));
		
	if(dns_number>=3)
	{
		printf("hostname %s dns error\n", SOCK_TARGET_IP);
		return -1;
	}
		
	
	/* tcp连接 */
	if(tcp_client_connect(ipbuf, MQTT_PORT, SOCKET_MQTT)!=0)
		return -1;
	
	//---------------mqtt连接信息------------------------
	data.cleansession = 1;							//0:订阅客户机掉线，保存为其推送的消息,1：
	data.MQTTVersion  = 4;  							//MQTT版本
	data.clientID.cstring  = "2e266e 2a";			//客户端ID
	data.keepAliveInterval = MQTT_PING_TIMER+10;	//mqtt服务器保持和客户端的连接时间 0表示一直连接

	//	//---------------用户名，密码-------------------------
	//	data.username.cstring = "admin";
	//	data.password.cstring = "admin";

	//---------------遗嘱，客户端非正常关闭服务器发送遗嘱消息-------------------------
	data.willFlag = 1;  						//遗嘱标志
	data.will.qos = 1;						//遗嘱等级
	data.will.retained = 0;					//服务器是否保留遗嘱消息
		
	data.will.topicName.cstring = "G/tt";		//遗嘱主题
	data.will.message.cstring   = "abcd";		//遗嘱负载

	len = MQTTSerialize_connect(buf, MQTT_PACKET_SIZE_MAX, &data);	/* 整合发送数据流，将结构体数据整合成数组*/
	if (mqtt_sendPacketBuffer(buf, len) >0)
	{
		/* 等待服务器的连接回复应答 */
		if (MQTTPacket_read(buf, MQTT_PACKET_SIZE_MAX, &mqtt_getdata) == CONNACK)
		{
			unsigned char sessionPresent, connack_rc;

			if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, MQTT_PACKET_SIZE_MAX) != 1 || connack_rc != 0)
			{
				printf("Unable to connect, return code %d\n", connack_rc);
				return -1;
			}
		}
	}
	return 0;
}

/******************************************************************************
 * @fn      mqtt_publish
 *
 * @brief  	MQTT通过TCP推送一个主题
 *
 * @param   pTopic:推送主题		pMessage:消息内容
 *
 * @return  0：成功      -1：失败
 *****************************************************************************/
int mqtt_publish(char *pTopic, char *pMessage)
{
	uint8_t   buf[MQTT_PACKET_SIZE_MAX];
	uint32_t  payload_leng, pub_leng;
	
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = pTopic;		/* publish topic*/
	payload_leng = strlen(pMessage);	/* 推送主题负载长度 */
	
	/* 序列化推送消息 */
	pub_leng = MQTTSerialize_publish(buf, MQTT_PACKET_SIZE_MAX, 0, 0, 0, 0, topicString, (uint8_t *)pMessage, payload_leng);
	if (mqtt_sendPacketBuffer( buf, pub_leng) > 0)/* tcp发送数据流 */
	{
		printf("publish topic %s success\n", pTopic);
		return 0;
	}
	else
	{
		printf("publish topic error\n");	
		return -1;
	}	
}

/******************************************************************************
 * @fn      mqtt_subscribe
 *
 * @brief  	MQTT通过TCP订阅一个主题
 *
 * @param   pTopic:订阅主题
 *
 * @return  0：成功
 *****************************************************************************/
int mqtt_subscribe(char *pTopic)
{
    uint32_t sub_leng;
    uint8_t buf[MQTT_PACKET_SIZE_MAX];
	int req_qos = 0;
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = pTopic;		//订阅主题名
	
	sub_leng = MQTTSerialize_subscribe(buf, MQTT_PACKET_SIZE_MAX, 0, 1, 1, &topicString, &req_qos);/* 序列化主题订阅主题消息*/
	if (mqtt_sendPacketBuffer(buf, sub_leng) > 0)
	{
		if (MQTTPacket_read(buf, MQTT_PACKET_SIZE_MAX, &mqtt_getdata) == SUBACK) 	/* wait for suback */
		{
			unsigned short submsgid;
			int subcount;
			int granted_qos;

			MQTTDeserialize_suback(&submsgid, 1, &subcount, &granted_qos, buf, MQTT_PACKET_SIZE_MAX);
			if (granted_qos != 0)
			{
				printf("granted qos != 0, %d\n", granted_qos);
				return 0;
			}
		}
		return 0;
	}	
	else
	{
		return -1;
	}
}


//解析mqtt主题
mqtt_topic topic_analyze(char * topic_sting,int Len)
{
	mqtt_topic topic;
	
	char* index ;
	char* index1;
	index = strchr(topic_sting, '/');
	strncpy(topic.type, topic_sting, index - topic_sting);
	topic.type[index - topic_sting+1] = '\0';
	index1 = strchr(index+1, '/');
	strncpy(topic.cmd,index+1, index1-index-1);
	topic.cmd[index1-index] = '\0';
	strncpy(topic.mac,index1+1, Len - (index1-topic_sting+1));
	topic.mac[Len - (index1-topic_sting+1)+1] = '\0';
	return topic;
}

