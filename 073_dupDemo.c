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
	if(fd1==-1)
		perr_exit("open error");

	int fd2=dup(fd1);
	if(fd2==-1)
		perr_exit("dup error");

	printf("fd1=%d	fd2=%d\n",fd1,fd2);

	write(fd2,"fuckyou\n",8);

	return 0;
}
