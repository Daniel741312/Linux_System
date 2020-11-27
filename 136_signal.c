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
#include<signal.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

void catch_signal(int signum){
	printf("Catch you!!!%d\n",signum);
}

int main(int argc,char* argv[]){

	signal(SIGINT,catch_signal);

	while(1);

	return 0;
}

