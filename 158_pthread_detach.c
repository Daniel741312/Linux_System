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

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

void* tfn(void* arg){
	printf("tfn:pid=%d,tid=%lu\n",getpid(),pthread_self());
	return NULL;
}

int main(int argc,char* argv[]){
	int ret=0;
	pthread_t tid=0;

	ret=pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0){
		fprintf(stderr,"pthread_create error%s\n",strerror(ret));
		exit(1);
	}

	ret=pthread_detach(tid);
	if(ret!=0){
		fprintf(stderr,"pthread_detach error%s\n",strerror(ret));
		exit(1);
	}

	sleep(1);

	ret=pthread_join(tid,NULL);
	if(ret!=0){
		fprintf(stderr,"pthread_join error%s\n",strerror(ret));
		exit(1);
	}

	printf("main:pid=%d,tid=%lu\n",getpid(),pthread_self());
	pthread_exit(NULL);
	return 0;
}
