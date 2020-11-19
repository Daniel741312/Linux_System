#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int var=100;

int main(int argc,char* argv[]){
	pid_t pid=fork();
	if(pid==-1)
		perr_exit("fork error");
	
	if(pid==0){
		var=288;
		printf("I'm child,my pid=%d,my parent's pid=%d\n",getpid(),getppid());
		printf("My var=%d\n\n",var);
	}else if(pid>0){
		var=200;
		printf("I'm parent,my pid=%d,my parent's pid=%d\n",getpid(),getppid());
		printf("My var=%d\n\n",var);

	}


	return 0;
}
