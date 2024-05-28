#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD	100

void * thread_inc(void * arg);
void * thread_des(void * arg);
void * thread_mul(void * arg);
long long num=1;

int main(int argc, char *argv[]) 
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	printf("sizeof long long: %zu \n", sizeof(long long));
	for(i=0; i<NUM_THREAD; i++)
	{
		if(i%3==1)
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else if(i%3==2)
			pthread_create(&(thread_id[i]), NULL, thread_mul, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);	
	}	

	for(i=0; i<NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL);

	printf("result: %lld \n", num);
	return 0;
}

void * thread_inc(void * arg) 
{
	int i;
	for(i=0; i<5000; i++)
		num+=1;
	return NULL;
}
void * thread_des(void * arg)
{
	int i;
	for(i=0; i<5000; i++)
		num-=1;
	return NULL;
}
void * thread_mul(void * arg){
	int i;
	for(i=0;i<5000;i++)
		num *=1;
	return NULL;
}