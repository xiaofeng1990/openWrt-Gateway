本工程为网关工程
硬件：mt7688

文件目录介绍
1.applications目录
	该目录存放设备管理，情境管理，定时管理，联动管理文件，网关和服务器的心跳函数，网关和子设备之间的心跳
2.conmmon目录
	该目录为用户的一些共用的函数，md5校验，字符串转换和处理文件，json数据处理
3.drivers目录
	该目录存放底层硬件的驱动函数和一些底层封装函数，数据库，tcp，mqtt，usart
4.include目录
	该目录存放头文件
5.log目录
	该目录存放控制记录日志和错误日志
6.mqtt目录
	该目录存放mqtt客户端协议源码
7.threads目录
	该目录存放进程相关的函数
8.ipc目录
	ipc（Interprocess communication）存放进程通信的函数，比如信号量，邮箱，队列
9.document目录
	该目录存放网关文档