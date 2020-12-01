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

	printf("main:pid=%d,tid=%lu\n",getpid(),pthread_self());

	ret=pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0)
		perr_exit("pthread_create error");

	/*父进程等待1秒,否则父进程一旦退出,地址空间被释放,子线程没机会执行*/
	sleep(1);
	return 0;
}
