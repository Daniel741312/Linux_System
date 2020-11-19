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
	printf("---before fork 1---\n");
	printf("---before fork 2---\n");
	printf("---before fork 3---\n");
	printf("---before fork 4---\n");

	pid_t pid=0;
	pid=fork();
	
	if(pid==-1)
		perr_exit("---fork error---\n");
	else if(pid==0)
		printf("---I'm child,my pid is %d,my parent's pid is %d---\n",getpid(),getppid());
	else if(pid>0)
		printf("---I'm parent,my pid is %d,my child's pid is %d---\n---My parent's pid is %d---\n",getpid(),pid,getppid());

	printf("---end of file---\n\n");
	return 0;
}
