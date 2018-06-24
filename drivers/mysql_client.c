#include "debug.h"
#include "mysql_client.h"

/**
  * @fn     mysql_connect
  * @brief  先初始化数据库句柄，并连接到本地数据库，
  * @param  gatewayInfo: 网关info结构体，这里用到数据库的句柄
  * @retval 0: sucessce; other: error;
  */
int mysql_connect(struct tGatewayInfo *gatewayInfo)
{  
    if (NULL==mysql_init(&gatewayInfo->mysql.db)) 
	{
		DEBUG_LOG("mysql_init(): %s\n", mysql_error(&gatewayInfo->mysql.db));
		return -1;
    }

    if(NULL == mysql_real_connect(&gatewayInfo->mysql.db, HOST, USER, PASSWD, DB_NAME, 0, NULL, 0)) 
	{  
        DEBUG_LOG("mysql_real_connect(): %s\n", mysql_error(&gatewayInfo->mysql.db));  
        return -1;  
    } 
    DEBUG_LOG("Connected MySQL successful! \n");
	return 0;
}

/**
  * @fn     mysql_disconnect
  * @brief  关闭数据库
  * @param  MYSQL *mysql: 数据库结构体指针，为调用mysql_init后的句柄
  * @retval NULL
  */
void mysql_disconnect(MYSQL *mysql)
{
    mysql_close(mysql);
}
 

/**
  * @fn     mysql_handle_cmd
  * @brief  执行操作mysql数据库命令函数，执行删除记录，插入记录，修改记录的
  *			命令
  * @param  MYSQL *mysql: 数据库结构体指针，为调用mysql_init后的句柄
  * @param	char *cmd: 执行命令的字符串
  * @prarm	int len: 执行命令字符串的长度
  * @retval 0: sucessce; other: error;
  */
int mysql_handle_cmd(MYSQL *mysql, char *cmd, int len)
{  
    if (mysql_real_query(mysql, cmd, len)) 
	{  
        DEBUG_LOG("mysql failed to executive cmd: %s\n", mysql_error(mysql));  
        return -1;
    }  
    DEBUG_LOG("mysql executive cmd sucessfully!\n");
	return 0;
}  

 
/**
  * @fn     mysql_find_cmd
  * @brief  执行查找mysql数据库命令函数，查找子设备，情境，定时信息命令
  * 		在调用完该函数后，并且解析完返回数据，一定要调用mysql_free_result
  *         函数释放内存
  * @param  MYSQL *mysql: 数据库结构体指针，为调用mysql_init后的句柄
  * @param  MYSQL_RES *res: 该参数为输出参数，当查询完数据库后，将返回
  *			结果的内存地址赋值给该参数 
  * @param	char *cmd: 执行命令的字符串
  * @prarm	int len: 执行命令字符串的长度
  * @retval 0: sucessce; other: error;
  */
int mysql_find_cmd(MYSQL *mysql, MYSQL_RES *res, char *cmd, int len)
{  
	int i;					
	int fields; 			//一行中有多少个字段 
    int rows;	            //总共有多少行数据
    char *query ="show databases";
	
	if(mysql_real_query(mysql, cmd, len)) 
	{  
        DEBUG_LOG("mysql failed to executive cmd: %s\n", mysql_error(mysql));  
        return -1;
    }
	
	/* 存储查询结果 */
    res = mysql_store_result(mysql);
    if (NULL == res) 
	{  
         DEBUG_LOG("mysql_store_result(): %s\n", mysql_error(mysql));  
         return -1;  
    }
	
	/* 获得行数 */
	//rows = mysql_num_rows(res);  
    //DEBUG_LOG("The total rows is: %d\n", rows);
	/* 获得一行的字段数 */
    //fields = mysql_num_fields(res);  
    //DEBUG_LOG("The total fields is: %d\n", fields); 
	return 0;
}
 
 
/* 显示所有数据库 */
/**
  * @fn     mysql_show_databases
  * @brief  显示数据库所有内容
  * @param  MYSQL *mysql: 数据库结构体指针，为调用mysql_init后的句柄 
  * @retval 0: sucessce; other: error;
  */
int mysql_show_databases(MYSQL *mysql)  
{  
    int err;  
	int i;					
	int fields; 			//一行中有多少个字段 
    int rows;	            //总共有多少行数据
    char *query ="show databases";
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	
	/* 发送指令 */
    err = mysql_real_query(mysql, query, strlen(query));  
    if (err != 0) 
	{  
        DEBUG_LOG("Failed to query: %s\n", mysql_error(mysql));
        return -1;
    }  
	
	/* 存储查询结果 */
    res = mysql_store_result(mysql);
    if (NULL == res) 
	{  
         DEBUG_LOG("mysql_store_result(): %s\n", mysql_error(mysql));  
         return -1;  
    }
	
	rows = mysql_num_rows(res);  
    DEBUG_LOG("The total rows is: %d\n", rows);  
	
	/* 获取下一行数据，NULL为失败 */
    while (row = mysql_fetch_row(res))
	{	
		fields = mysql_num_fields(res); 
		DEBUG_LOG("The total fields is: %d\n", fields);
		/* 获得一行中有几个字段 */
        for(i = 0; i < fields; i++) 
		{
            DEBUG_LOG("%s\t",row[i]);
        }  
        DEBUG_LOG("\n");
    }
	
	/* 释放内存 */
    mysql_free_result(res);
	
	return 0;
}
