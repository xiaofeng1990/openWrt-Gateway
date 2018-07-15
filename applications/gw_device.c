;
#include "gw_device.h"
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>
#include "user_string.h"
#include "debug.h"

#include<pthread.h>
#include<time.h>


/* 添加设备 */
int dm_add_device(char *json_data, struct tGatewayInfo *gateway_info)
{
	int err;  
    struct timespec tout; 
	
	struct tDeviceInfo *pTemp;
	int ret = 0;
	/* 分配内存 */
	pTemp = (struct tDeviceInfo *)malloc(sizeof(struct tDeviceInfo));
	if(pTemp == NULL)
	{
		DEBUG_LOG("Malloc sub device info error!\n");
		free(pTemp);

		/* 向日志数据库中写错误类型 */
		
		return 16;
	}
	else
	{
		memset(pTemp, 0, sizeof(struct tDeviceInfo));
		DEBUG_LOG("Malloc sub device info succeed!\n");
	}
	
	/* 解析json数据 */
	if(dm_parse_json(json_data, pTemp))
	{
		free(pTemp);
		return 30;
	}
	
	/* 验证是否是重复添加 */
	if(dm_find_dev_by_mac(gateway_info->dev_list, pTemp->mac) != NULL)
	{
		DEBUG_LOG("device is exist!\n");
		free(pTemp);
		return 17;
	}

	/* 向电力载波模块发送添加设备指令 */
	clock_gettime(CLOCK_REALTIME, &tout);   
    tout.tv_sec += FSN_TIME_OUT;   //延迟5s 
    err = pthread_mutex_timedlock(&gateway_info->fsn.mutex_fsn, &tout); 
	if(err == 0)
	{

	}
	else
	{
		DEBUG_LOG("wait for the mutex of the fsn timeout: %s!\n", strerror(err));
		free(pTemp);
		return 20;
	}
	/* 等待条串口件变量 */
	/* 将设备注册到设备列表中 */
	
	/* 同步数据库 */
	
}

/***************************************************************************************************
 * @fn      dm_parse_json
 *
 * @brief   解析json数据到设备结构体中
 *
 * @param   json_data：json数据字符串        pDevice_info：子设备结构体
 *			
 * @return  30：json数据不完整        0：解析完成
***************************************************************************************************/
int dm_parse_json(char *json_data, struct tDeviceInfo *device_info)
{
	cJSON* root;
	cJSON* data;
	cJSON *item;	

	/* 验证json数据的完成性 */
	root = cJSON_Parse(json_data);
	if(root == NULL)
	{
		DEBUG_LOG("cjson data error!\r\n");
		cJSON_Delete(root);
		return 30;
	}

	/* 验证时间戳有效性 */

	/* 解析json数据 */
	
	item = cJSON_GetObjectItem(json_data, "name");
	if(item != NULL)
	{
		strncpy( device_info->name, item->valuestring, strlen(item->valuestring));
		DEBUG_LOG("sub device name = %s\r\n", device_info->name);
	}	
	
	item = cJSON_GetObjectItem(json_data, "type");
	if(item != NULL)
	{
		device_info->type = (uint16_t)item->valueint;
		DEBUG_LOG("sub device type = %d \r\n", device_info->type);
	}
	
	item = cJSON_GetObjectItem(json_data, "mac");
	if(item != NULL)
	{
		srting_to_hex(device_info->mac, (uint8_t *)item->valuestring, strlen(item->valuestring)/2);
		DEBUG_LOG("sub device mac = %s \r\n", item->valuestring);
	}
	
	item = cJSON_GetObjectItem(json_data, "zone");
	if(item != NULL)
	{
		device_info->zone = (uint32)item->valueint;
		DEBUG_LOG("sub device zone = %d\r\n",device_info->zone);
	}
	
	item = cJSON_GetObjectItem(json_data, "icon");
	if(item != NULL)
	{
		device_info->icon = item->valueint;
		DEBUG_LOG("sub device icon = %d\r\n",device_info->icon);
	}
	
	
	item = cJSON_GetObjectItem(json_data, "user");
	if(item != NULL)
	{
		device_info->user = (uint32)item->valueint;
		DEBUG_LOG("sub device user = %d\r\n",device_info->user);
	}
	
	item = cJSON_GetObjectItem(json_data, "time");
	if(item != NULL)
	{
		device_info->ping_time = str_to_u32(item->valuestring);
		DEBUG_LOG("sub device pingTime = %d\r\n",device_info->ping_time);
	}
	
	item = cJSON_GetObjectItem(json_data, "state");
	if(item != NULL)
	{
		strncpy( device_info->data, item->valuestring, strlen(item->valuestring));
		DEBUG_LOG("sub device state = %s \r\n", item->valuestring);
	}

	cJSON_Delete(root);

	return 0;
}

/* 删除设备 */
int dm_delete_device()
{
	/* 验证json数据完成性 */

	/* 解析json数据 */
	
	/* 验证时间戳有效性 */

	/* 释放场景、定时中设备内存，同步场景、定时数据库 */

	/* 释放设备列表中的内存，同步数据库 */
}

/* 编辑设备 */
int dm_editor_device()
{
	/* 验证json数据完成性 */

	/* 解析json数据 */
	
	/* 验证时间戳有效性 */

	/* 将新的设备属性同步到设备类表中，并更新数据库 */
}

/* 执行设备 */
int dm_exe_device()
{
	
}
/* 查找设备 */
/* 通过名称查找 */
/* 通过MAC地址查找 */
/***************************************************************************************************
 * @fn      dm_find_dev_by_mac
 *
 * @brief   从设备列表中按设备mac查找设备
 *
 * @param   dev_list：设备列表        mac：子设备mac
 *			
 * @return  tDeviceInfo *：子设备结构体地址            NULL：设备不存在
***************************************************************************************************/
struct tDeviceInfo *dm_find_dev_by_mac(struct tDeviceInfo *dev_list, uint8_t *mac)
{
	//int memcmp( const void *buffer1, const void *buffer2, size_t count );
	struct tDeviceInfo *pTemp = dev_list;

	/* 遍历子设备列表 */
	while(pTemp)
	{
		if(memcmp(pTemp->mac, mac, DEV_MAC_LEN)==0)
			return pTemp;
		pTemp = pTemp->next;
	}

	/* 没找到就返回 NULL */
	return NULL;
}

/* 通过 */
/*  */


/* 上报服务器设备列表 */
int dm_report_dev_link_to_server()
{
	
}
/*  */





