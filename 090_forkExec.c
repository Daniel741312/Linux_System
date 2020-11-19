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

int main(int argc,char* argv[]){

	pid_t pid=fork();
	if(pid==-1)
		perr_exit("fork error");

	if(pid==0){
		/*好家伙,参数从argv[0]开始算*/
		//execlp("ls","ls","-l","-R","-h",NULL);
		execl("./test","./test",NULL);
		/*正常情况下是不会执行到这里的,只有当出错时才会返回到这里执行*/
		perror("execlp error");
		exit(1);
	}else if(pid>0){
		printf("I'm parent:%d\n",getpid());
		sleep(1);
	}

	return 0;
}