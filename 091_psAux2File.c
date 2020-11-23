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

	int ret=0;
	int fd1=0;
	fd1=open("ps.log",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd1==-1)
		perr_exit("open error");


	ret=dup2(fd1,STDOUT_FILENO);
	if(ret==-1)
		perr_exit("dup2 error");

	execlp("ps","ps","aux",NULL);
	perror("execlp error");
	exit(1);

	return 0;
}