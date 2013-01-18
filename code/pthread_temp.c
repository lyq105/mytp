/************************************************************
 * 
 *  This is a simple example for using pthread.
 *
 *
 *  the compile rule of this simple program is 
 *
 *  		gcc -o pthread pthread_temp.c -lpthread
 *
 *
 * **********************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER_OF_THREAD 2

// Thread 1's worker function.
void* worker(void* arg)
{
	static int ret = 1;
	char* hello_str = (char*) arg;
	sleep(2);
	printf("%s\n", hello_str);
	pthread_exit(&ret);
}


// the main function of this program.
int main(int argc, const char *argv[])
{
	int ret = 0;
	int i;
	pthread_t pt[NUMBER_OF_THREAD];

	argv[0] = "hello from thread 1";
	argv[1] = "hello from thread 2";
	printf("Begin to creat threads\n");
	
	ret = pthread_create(&pt[0],NULL,worker,(void*)argv[0]);
	printf("%d\n",ret);
	ret = pthread_create(&pt[1],NULL,worker,(void*)argv[1]);
	printf("%d\n",ret);

	for (i = 0; i < NUMBER_OF_THREAD; i++) {
		ret = pthread_join(pt[i],NULL);
	}

	printf("Now the main function is over!\n");
	return 0;
}
