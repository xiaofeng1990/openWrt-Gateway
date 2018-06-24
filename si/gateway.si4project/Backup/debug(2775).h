
#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
 
#define _DEBUG_LEVEL_ 2  

#if 1==_DEBUG_LEVEL_    	//普通打印  
	#define DEBUG_LOG printf
#elif 2==_DEBUG_LEVEL_ 	 	//打印文件名、行号  
	#define DEBUG_LOG (printf("%s(%d): ", __FILE__, __LINE__), printf)  
#elif 3==_DEBUG_LEVEL_  	//打印文件名、行号、函数名  
	#define DEBUG_LOG (printf("%s(%d)-<%s>: ", __FILE__, __LINE__, __FUNCTION__,), printf)  
#else  
	#define DEBUG_LOG  
#endif //_DEBUG_H  

#endif
