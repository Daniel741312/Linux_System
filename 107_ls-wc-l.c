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
	int fd[2];
	pid_t pid;
	int ret=0;

	ret=pipe(fd);
	if(ret==-1)
		perr_exit("pipe error");

	pid=fork();
	if(pid==-1)
		perr_exit("fork error");

	if(pid>0){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		perr_exit("execlp wc error");
	}else if(pid==0){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
		perr_exit("execlp ls error");
	}

	return 0;
}
