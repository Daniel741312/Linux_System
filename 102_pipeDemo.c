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
	int ret=0;
	int pipefd[2];
	pid_t pid=0;
	char* str="fuckyou\n";
	char buf[1024];

	ret=pipe(pipefd);
	if(ret==-1)
		perr_exit("pipe error");

	pid=fork();
	if(pid>0){
		close(pipefd[0]);
		sleep(3);
		write(pipefd[1],str,sizeof(str));
		close(pipefd[1]);
	}else if(pid==0){
		close(pipefd[1]);
		ret=read(pipefd[0],buf,sizeof(buf));
		write(STDOUT_FILENO,buf,ret);
		close(pipefd[0]);
	}

	return 0;
}