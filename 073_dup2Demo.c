#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){

	int fd1=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0644);

	int fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644);

	int fdret=dup2(fd1,fd2);
	printf("fdret=%d\n",fdret);

	int ret=write(fd2,"fuckyou\n",8);
	printf("ret=%d\n",ret);

	dup2(fd1,STDOUT_FILENO);
	printf("--------fuckyou--------\n");

	return 0;
}