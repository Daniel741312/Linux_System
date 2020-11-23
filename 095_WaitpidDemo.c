#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	int i=0;
	int wpid=0;
	int pid=0;
	int temppid=0;

	for(i=0;i<5;++i){
		pid=fork();
		if(pid==0)
			break;
		
		if(i==2)
			temppid=pid;
	}

	if(i==5){
		//wpid=waitpid(-1,NULL,WNOHANG);		//以非阻塞的方式回收任意子进程
		sleep(5);
		wpid=waitpid(temppid,NULL,WNOHANG);
		if(wpid==-1)
			perr_exit("waitpid error");
		printf("I'm parent,wait a child finish:%d\n",wpid);
	}
	else{
		sleep(i);
		printf("I'm %dth child,my pid=%d\n",i+1,getpid());
	}

	sleep(1);
	return 0;
}
