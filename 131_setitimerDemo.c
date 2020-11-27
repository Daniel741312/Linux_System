#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/time.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

void myfunc(int signo){
	printf("fuckyou\n");
	return;
}

int main(int argc,char* argv[]){
	signal(SIGALRM,myfunc);
	int ret=0;

	struct itimerval oldit;

	struct itimerval it;
	it.it_value.tv_sec=2;
	it.it_value.tv_usec=0;
	it.it_interval.tv_sec=5;
	it.it_interval.tv_usec=0;


	ret=setitimer(ITIMER_REAL,&it,&oldit);
	if(ret==-1)
		perr_exit("setitimer error");

	while(1);
	return 0;
}
