#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<dirent.h>
#include<signal.h>
#include<pthread.h>
#include<time.h>

/*创建一把全局锁*/
pthread_mutex_t mutex;

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

void* tfn(void* arg){
	srand(time(NULL));
	while(1){
		/*子线程先加锁再访问*/
		pthread_mutex_lock(&mutex);
		printf("hello ");
		sleep(rand()%3);
		printf("world\n");
		/*访问完立即解锁*/
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	return NULL;
}

int main(int argc,char* argv[]){
	pthread_t tid;
	int ret=0;
	srand(time(NULL));

	/*在main函数中将锁初始化*/
	ret=pthread_mutex_init(&mutex,NULL);
	if(ret!=0)
		perr_exit("pthread_mutex_init error",ret);

	ret=pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0)
		perr_exit("pthread_create error",ret);

	while(1){
		/*主线程先加锁再访问*/
		pthread_mutex_lock(&mutex);
		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");
		/*访问完立即解锁*/
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}

	pthread_mutex_destroy(&mutex);
	pthread_join(tid,NULL);
	return 0;
}
