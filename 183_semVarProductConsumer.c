#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM 5

int queue[NUM];
sem_t blank_num,product_num;

void* producter(void* arg){
	int i=0;

	while(1){
		sem_wait(&blank_num);
			queue[i]=rand()%1000+1;
			printf("====Producter:%d\n",queue[i]);
		sem_post(&product_num);

		i=(i+1)%NUM;
		sleep(rand()%3);
	}
	return NULL;
}

void* consumer(void* arg){
	int i=0;

	while(1){
		sem_wait(&product_num);
			printf("----Consumer:%d\n",queue[i]);
			queue[i]=0;
		sem_post(&blank_num);

		i=(i+1)%NUM;
		sleep(rand()%3);
	}
	return NULL;
}

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

int main(int argc,char* argv[]){

	srand(time(NULL));
	pthread_t pid,cid;

	sem_init(&blank_num,0,NUM);
	sem_init(&product_num,0,0);

	/*创建两个子线程*/
	pthread_create(&pid,NULL,producter,NULL);
	pthread_create(&cid,NULL,consumer,NULL);

	/*回收两个子线程*/
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);

	sem_destroy(&blank_num);
	sem_destroy(&product_num);

	return 0;
}