#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<signal.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	pid_t pid=fork();

	if(pid>0){
		printf("I'm parent,pid=%d\n",getpid());
		while(1);

	}else if(pid==0){
		printf("I'm child,pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(2);
		kill(getppid(),SIGKILL);
	}

	return 0;
}
