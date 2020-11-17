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

	if(S_ISREG(sbuf.st_mode))
		printf("It's a regular\n");
	else if(S_ISDIR(sbuf.st_mode))
		printf("It's a dir\n");
	else if(S_ISFIFO(sbuf.st_mode))
		printf("It's a pipe\n");
	else if(S_ISLNK(sbuf.st_mode))
		printf("It's a symbol");
	/*and so on*/

	return 0;
}
