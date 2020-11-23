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

	for(i=0;i<5;++i){
		pid=fork();
		if(pid==0)
			break;
	}

	if(i==5){
		while((wpid=waitpid(-1,NULL,WNOHANG))!=-1){
			if(wpid>0)
				printf("wait chile:%d\n",wpid);
			else if(wpid==0)
				sleep(1);
		}
	}else{
		sleep(i);
		printf("I'm %dth child,my pid=%d\n",i+1,getpid());
	}

	sleep(1);
	return 0;
}
