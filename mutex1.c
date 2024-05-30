#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREAD	100

void * thread_inc(void * arg);
void * thread_des(void * arg);

long long num=0;
//pthread_mutex_t mutex;
static sem_t sem;

int main(int argc, char *argv[]) 
{
	pthread_t thread_id[NUM_THREAD];
   
	int i;
	 sem_init(&sem, 0, 1);
	//pthread_mutex_init(&mutex, NULL);

	for(i=0; i<NUM_THREAD; i++)
	{
		if(i%2)
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);	
	}	

	for(i=0; i<NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL);

	printf("result: %lld \n", num);
	//pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
	return 0;
}

void * thread_inc(void * arg) 
{
	int i;
	//pthread_mutex_lock(&mutex);
    sem_wait(&sem);

	for(i=0; i<5000; i++)
		num+=1;
    sem_post(&sem);
	//pthread_mutex_unlock(&mutex);
	return NULL;
}
void * thread_des(void * arg)
{
	int i;
	for(i=0; i<5000; i++)
	{
		//pthread_mutex_lock(&mutex);
        sem_wait(&sem);
		num-=1;
		sem_post(&sem);
        //pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

