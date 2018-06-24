#include <stdio.h>

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


pthread_t key_thread;

void *key_thread_f()
{
	printf ("key thread: I'm key thread\n");

	while(1)
	{
		printf("key thread is run\n");
		sleep(4);
	}
	pthread_exit(0);
}

void key_thread_create(void)
{
	int temp;
	memset(&key_thread, 0, sizeof(pthread_t)); 
	/*创建线程*/
	if((temp = pthread_create(&key_thread, NULL, key_thread_f, NULL)) != 0)     
		printf("key thread is err!\n");
	else
		printf("key thread is ok\n");

}

