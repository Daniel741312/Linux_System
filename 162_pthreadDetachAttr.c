#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>
#include<pthread.h>

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

void* tfn(void* arg){
	printf("tfn:pid=%d,tid=%lu\n",getpid(),pthread_self());
	return NULL;
}

int main(int argc,char* argv[]){
	int ret=0;
	pthread_t tid=0;
	pthread_attr_t attr;
	/*初始化属性结构体*/
	ret=pthread_attr_init(&attr);
	if(ret!=0)
		perr_exit("pthread_attr_init error",ret);
	/*给属性结构体添加分离属性*/
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if(ret!=0)
		perr_exit("pthread_attr_setdetachstate error",ret);

	printf("main:pid=%d,tid=%lu\n",getpid(),pthread_self());
	/*创建子线程*/
	ret=pthread_create(&tid,&attr,tfn,NULL);
	if(ret!=0)
		perr_exit("pthread_create error",ret);
	/*join一下试试,由于线程已经分离了,会出错*/
	ret=pthread_join(tid,NULL);
	if(ret!=0)
		perr_exit("pthread_join error",ret);
	/*销毁线程属性结构体*/
	ret=pthread_attr_destroy(&attr);
	if(ret!=0)
		perr_exit("pthread_attr_destory error",ret);
	pthread_exit(NULL);
	return 0;
}