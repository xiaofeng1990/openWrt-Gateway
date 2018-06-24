
#include "gw_device.h"
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>
#include "user_string.h"


/* 添加设备 */
int dm_add_device(char *json_data, struct tDevice_info *pDevice_info)
{
	struct tDevice_info pTemp;
	
	/* 分配内存 */
	pTemp = (struct tDevice_info *)malloc(sizeof(struct tDevice_info));

	/* 解析json数据 */

	/* 验证是否是重复添加 */
	
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

int dm_parse_json(char *json_data, struct tDevice_info *pDevice_info)
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
		strncpy( pDevice_info->name, item->valuestring, strlen(item->valuestring));
		DEBUG_LOG("sub device name = %s\r\n", pDevice_info->name);
	}	
	
	item = cJSON_GetObjectItem(json_data, "type");
	if(item != NULL)
	{
		pDevice_info->type = (uint16_t)item->valueint;
		DEBUG_LOG("sub device type = %d \r\n", pDevice_info->type);
	}
	
	item = cJSON_GetObjectItem(json_data, "mac");
	if(item != NULL)
	{
		Srting_to_Hex(pDevice_info->mac, (uint8_t *)item->valuestring, strlen(item->valuestring)/2);
		DEBUG_LOG("sub device mac = %s \r\n", item->valuestring);
	}
	
	item = cJSON_GetObjectItem(json_data, "zone");
	if(item != NULL)
	{
		pDevice_info->zone = (uint32)item->valueint;
		DEBUG_LOG("sub device zone = %d\r\n",pDevice_info->zone);
	}
	
	item = cJSON_GetObjectItem(json_data, "icon");
	if(item != NULL)
	{
		pDevice_info->icon = item->valueint;
		DEBUG_LOG("sub device icon = %d\r\n",pDevice_info->icon);
	}
	
	
	item = cJSON_GetObjectItem(json_data, "user");
	if(item != NULL)
	{
		pDevice_info->user = (uint32)item->valueint;
		DEBUG_LOG("sub device user = %d\r\n",pDevice_info->user);
	}
	
	item = cJSON_GetObjectItem(json_data, "time");
	if(item != NULL)
	{
		pDevice_info->ping_time = str_to_u32(item->valuestring);
		DEBUG_LOG("sub device pingTime = %d\r\n",pDevice_info->ping_time);
	}
	
	item = cJSON_GetObjectItem(json_data, "state");
	if(item != NULL)
	{
		strncpy( pDevice_info->data, item->valuestring, strlen(item->valuestring));
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
/* 通过 */
/*  */


/* 上报服务器设备列表 */
int dm_report_dev_link_to_server
{
	
}
/*  */





