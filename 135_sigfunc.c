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

void print_set(sigset_t* set){
	int i=0;
	for(i=1;i<32;++i){
		if(sigismember(set,i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main(int argc,char* argv[]){
	sigset_t set,oldset,pedset;
	int ret=0;

	sigemptyset(&set);
	/*Ctrl+c*/
	sigaddset(&set,SIGINT);
	/*Ctrl+\*/
	sigaddset(&set,SIGQUIT);
	sigaddset(&set,SIGBUS);
	sigaddset(&set,SIGKILL);

	sigprocmask(SIG_BLOCK,&set,&oldset);
	if(ret==-1)
		perr_exit("sigpending error");
	
	while(1){
		ret=sigpending(&pedset);
		if(ret==-1)
			perr_exit("sigpending error");
		
		print_set(&pedset);
		sleep(1);
	}

	return 0;
}
