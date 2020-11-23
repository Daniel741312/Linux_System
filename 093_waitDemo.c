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
	pid_t pid,wpid;
	int status=0;

	pid=fork();
	if(pid==-1)
		perr_exit("fork error");

	if(pid==0){
		printf("I'm child:%d,my parent is %d,I'm going to sleep 10s\n",getpid(),getppid());
		sleep(10);
		printf("I'm child,I'm going to die\n");
		return 73;
	}else if(pid>0){
		//wpid=wait(NULL);		//不关心子进程退出原因
		wpid=wait(&status);
		if(wpid==-1)
			perr_exit("wait error");

		if(WIFEXITED(status))
			printf("My child exited with:%d\n",WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("My child killed by:%d\n",WTERMSIG(status));

		printf("I'm parent,wait %d finish\n",wpid);
	}
	return 0;
}

