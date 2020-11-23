#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	int fd=0;
	int i=0;
	char buf[4096];

	if(argc<2){
		printf("Enter like this:./a.out fifoname\n");
		return -1;
	}

	fd=open(argv[1],O_WRONLY);
	if(fd==-1)
		perr_exit("open error");

	while(1){
		sprintf(buf,"fuckyou:%d\n",i++);
		write(fd,buf,strlen(buf));
		sleep(1);
	}

	close(fd);
	return 0;
}