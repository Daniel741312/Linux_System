#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc,char* argv[]){
	struct stat sbuf;
	int ret=0;
	ret=stat(argv[1],&sbuf);
	if(ret==-1){
		perror("stat error");
		exit(1);
	}

	printf("file size:%ld\n",sbuf.st_size);
	return 0;
}
