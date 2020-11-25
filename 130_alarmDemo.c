#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	int i=0;
	int j=0;
	alarm(1);

	while(1){
		printf("i=%d,j=%d\n",i,j);
		++i;
		j++;
	}

	return 0;
}
