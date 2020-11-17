#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	int fd=0;
	int ret=0;
	char* p="test of unlink\n";
	char* p2="after write something\n";

	fd=open("temp.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
	if(fd<0)
		perr_exit("open file error");

	ret=write(fd,p,strlen(p));
	if(ret==-1)
		perr_exit("write error");

	printf("hello,I'm printf\n");
	ret=write(fd,p2,strlen(p2));
	if(ret==-1)
		perr_exit("write error");

	printf("Entry key to continue\n");
	p[3]='a';
	getchar();
	close(fd);

	ret=unlink("temp.txt");
	if(ret==-1)
		perr_exit("unlink error");

	return 0;
}
