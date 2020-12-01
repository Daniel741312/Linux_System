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
	int i=(int)arg;
	printf("I'm %dth thread,pid=%d,tid=%lu\n",i+1,getpid(),pthread_self());
	sleep(i);
	return NULL;
}

int main(int argc,char* argv[]){
	int i=0;
	int ret=0;
	pthread_t tid=0;

	for(i=0;i<5;++i){
		ret=pthread_create(&tid,NULL,tfn,(void*)i);
		if(ret!=0)
			perr_exit("pthread_create error");
	}
	sleep(i);
	return 0;
}