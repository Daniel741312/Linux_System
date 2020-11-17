#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc,char* argv[]){

	int ret=0;
	ret=link(argv[1],argv[2]);
	if(ret==-1){
		perror("link error");
		exit(1);
	}

	ret=unlink(argv[1]);
	if(ret==-1){
		perror("unlink error");
		exit(1);
	}
	return 0;
}
