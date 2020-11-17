#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[]){
	int fd1=0;
	int fd2=0;

	/*Read a file by trunc,if it doesn't exist then create it with the mode 0644*/
	fd1=open("./dirt.txt",O_RDONLY|O_CREAT|O_TRUNC,0644);
	/*Read a file which doesn't exist*/
	fd2=open("./dirt2.txt",O_RDONLY);

	printf("fd1=%d\n",fd1);
	printf("fd2=%d,errno=%d:%s\n",fd2,errno,strerror(errno));

	close(fd1);
	close(fd2);
	return 0;
}
