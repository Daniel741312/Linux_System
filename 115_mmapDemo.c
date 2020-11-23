#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	char* p=NULL;
	int fd=0;
	int len=0;
	int ret=0;

	fd=open("./testmap",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
		perr_exit("open error");

	/*
	lseek(fd,10,SEEK_END);
	write(fd,"\0",1);
	*/

	ret=ftruncate(fd,20);
	if(ret==-1)
		perr_exit("ftruncate error");

	len=lseek(fd,0,SEEK_END);

	p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
		perr_exit("mmap error");

	/*内存的写操作,会被映射到文件的写操作*/
	strcpy(p,"fuckyou\n");
	/*内存的读操作,会被映射到文件的读操作*/
	printf("----%s\n",p);

	ret=munmap(p,len);
	if(ret==-1)
		perr_exit("munmap error");

	return 0;
}