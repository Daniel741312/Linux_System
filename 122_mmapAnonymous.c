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

int var=100;

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	pid_t pid=0;
	int* p=NULL;
	int ret=0;

	p=(int*)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
	if(p==MAP_FAILED)
		perr_exit("mmap error");

	pid=fork();
	if(pid==-1)
		perr_exit("fork error");

	if(pid==0){
		*p=9527;
		var=200;
		printf("I'm child,*p=%d,var=%d\n",*p,var);
	}else if(pid>0){
		sleep(1);
		printf("I'm parent,*p=%d,var=%d\n",*p,var);
		wait(NULL);

		ret=munmap(p,4);
		if(ret==-1)
			perr_exit("munmap error");
	}
	return 0;
}