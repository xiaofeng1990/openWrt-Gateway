#ifndef __MYSQL_CLIENT_H__
#define __MYSQL_CLIENT_H__

#define HOST    "127.0.0.1"
#define USER    "root"
#define PASSWD  "123"
#define DB_NAME "test"

int mysql_connect(MYSQL *mysql);
void mysql_disconnect(MYSQL *mysql);
int mysql_handle_cmd(MYSQL *mysql, char *cmd, int len);
int mysql_find_cmd(MYSQL *mysql, MYSQL_RES *res, char *cmd, int len);
int mysql_show_databases(MYSQL *mysql);

#endif  //__MYSQL_CLIENT_H__