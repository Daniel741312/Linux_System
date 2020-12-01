#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	pid_t pid=0;
	int ret=0;
	int fd=0;

	pid=fork();
	if(pid>0)
		exit(0);
	
	/*创建新会话*/
	pid=setsid();
	if(pid==-1)
		perr_exit("setsid error");

	ret=chdir("/home/daniel");
	if(ret==-1)
		perr_exit("chdir error");

	/*重设文件权限掩码*/
	umask(0022);

	/*关闭标准输入*/
	close(STDIN_FILENO);

	/*将标准输出和标准出错重定向到文件黑洞*/
	fd=open("/dev/null",O_RDWR);
	if(fd==-1)
		perr_exit("open error");
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);

	/*模拟业务逻辑*/
	while(1);

	return 0;
}
