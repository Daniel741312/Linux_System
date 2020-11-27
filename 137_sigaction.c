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
	if(signum==SIGINT)
		printf("Catch you SIGINT:%d\n",signum);
	else if(signum==SIGQUIT)
		printf("Catch you SIGQUIT:%d\n",signum);
}

int main(int argc,char* argv[]){

	int ret=0;

	struct sigaction act,oldact;
	act.sa_handler=catch_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	ret=sigaction(SIGINT,&act,&oldact);
	if(ret==-1)
		perr_exit("sigaction error");

	ret=sigaction(SIGQUIT,&act,&oldact);
	if(ret==-1)
		perr_exit("sigaction error");

	while(1);

	return 0;
}

