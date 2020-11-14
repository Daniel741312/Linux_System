#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[]){
	int fd1=0;
	int fd2=0;

	fd1=open("./dirt.txt",O_RDONLY|O_CREAT|O_TRUNC,0644);
	fd2=open("./dirt2.txt",O_RDONLY);

	printf("fd1=%d\n",fd1);
	printf("fd2=%d,errno=%d:%s\n",fd2,errno,strerror(errno));

	close(fd1);
	close(fd2);
	return 0;
}
