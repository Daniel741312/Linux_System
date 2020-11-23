#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<dirent.h>

int var=100;

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	int* p;
	pid_t pid;
	int fd=0;
	int ret=0;

	fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
		perr_exit("open error");
	ftruncate(fd,4);

	p=(int*)mmap(NULL,4,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
		perr_exit("mmap error");

	close(fd);

	pid=fork();
	if(pid==-1)
		perr_exit("fork error");
	
	if(pid==0){
		*p=2000;
		var=1000;
		printf("child:*p=%d,var=%d\n",*p,var);
	}else if(pid>0){
		sleep(1);
		printf("parent:*p=%d,var=%d\n",*p,var);
		wait(NULL);

		ret=munmap(p,4);
		if(ret==-1)
			perr_exit("munmap error");
	}
	return 0;
}
