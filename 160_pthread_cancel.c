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
#include<pthread.h>
#include<signal.h>

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

void* tfn(void* arg){
	while(1){
		printf("tfn:pid=%d,tid=%lu\n",getpid(),pthread_self());
		sleep(1);
	}
	return NULL;
}

int main(int argc,char* argv[]){
	int ret=0;
	pthread_t tid=0;

	printf("main:pid=%d,tid=%lu\n",getpid(),pthread_self());

	ret=pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0)
		perr_exit("pthread_create error",ret);

	sleep(5);
	ret=pthread_cancel(tid);
	if(ret!=0)
		perr_exit("pthread_cancel error",ret);
	

	while(1);
	pthread_exit(NULL);
	return 0;
}
