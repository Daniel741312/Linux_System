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
	int fd1=open(argv[1],O_RDWR|O_CREAT,0644);
	printf("fd1=%d\n",fd1);

	int newfd1=fcntl(fd1,F_DUPFD,0);
	printf("newfd1=%d\n",newfd1);

	int newfd2=fcntl(fd1,F_DUPFD,8);
	printf("newfd2=%d\n",newfd2);

	int ret=write(newfd2,"fuckyou\n",8);
	printf("ret=%d\n",ret);

	return 0;
}