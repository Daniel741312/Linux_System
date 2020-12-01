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

struct thrd{
	int var;
	char str[256];
};

void* tfn(void* arg){
	struct thrd* tval;
	tval=(struct thrd*)malloc(sizeof(struct thrd));

	tval->var=100;
	strcpy(tval->str,"fuckyou");

	return (void*)tval;
}

int main(int argc,char* argv[]){
	pthread_t tid=0;
	struct thrd* retval;
	int ret=0;

	ret=pthread_create(&tid,NULL,tfn,NULL);
	if(ret==-1)
		perr_exit("pthread_create error");

	ret=pthread_join(tid,(void**)&retval);
	if(ret==-1)
		perr_exit("pthread_join error");
	
	printf("child thread exit with var=%d,str=%s\n",retval->var,retval->str);

	pthread_exit(NULL);
	return 0;
}
