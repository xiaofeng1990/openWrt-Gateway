
#include "mqtt_client.h"
#include "MQTTPacket.h"

#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "thread_mqtt.h"

pthread_t mqtt_thread;
#define MQTT_PACKET_SIZE  2048


void *mqtt_thread_f()
{
	int msgtype;
	char topic_string[32];
	int ret = 0;	
	
	uint8_t buf[MQTT_PACKET_SIZE];
	pthread_detach(pthread_self());
	
	ret = mqtt_connect();
	if(ret == 0)
	{
		printf("mqtt connect success\n");
	}
	while(1)
	{	
		memset(buf, 0, MQTT_PACKET_SIZE);
		msgtype = MQTTPacket_read(buf, MQTT_PACKET_SIZE,  &mqtt_getdata);

		if (msgtype == PUBLISH) 	/* 判断是否是服务器推送的消息 */
		{
			unsigned char dup;
			int qos;
			unsigned char retained;
			unsigned short msgid;
			int payloadlen_in;
			unsigned char *payload_in;

			MQTTString receivedTopic;

			MQTTDeserialize_publish(&dup, &qos, &retained, &msgid, &receivedTopic, &payload_in, &payloadlen_in, buf, MQTT_PACKET_SIZE); 	/*序列化mqtt消息*/

			printf("payload:%d %s  \n", payloadlen_in, payload_in);
			if(payloadlen_in==MQTT_PACKET_SIZE) 
			{
				printf("mqtt data is to long\n");
				continue;
			}

			
		}
	}
	pthread_exit(0);
}

void mqtt_thread_create(void)
{
	int temp;
	memset(&mqtt_thread, 0, sizeof(mqtt_thread)); 
	/*创建线程*/
	if((temp = pthread_create(&mqtt_thread, NULL, mqtt_thread_f, NULL)) != 0)     
		printf("mqtt thread is err!\n");
	else
		printf("mqtt thread is ok\n");

}

void mqtt_thread_wait(void)
{
	/*等待线程结束*/
	if(mqtt_thread !=0)
	{ 
		pthread_join(mqtt_thread,NULL);
		printf("mqtt thread is over/n");
	}
}



