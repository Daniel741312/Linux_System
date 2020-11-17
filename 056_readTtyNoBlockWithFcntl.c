#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	int fd=0;
	char buf[10];
	int n=0;
	int ret=0;
	int flags=0;

	/*Set the file O_NONBLOCK by fcntl*/
	flags=fcntl(STDIN_FILENO,F_GETFL);
	if(flags==-1){
		perror("fcntl error");
		exit(1);
	}
	flags|=O_NONBLOCK;
	ret=fcntl(STDIN_FILENO,F_SETFL,flags);
	if(ret==-1){
		perror("fcntl error");
		exit(1);
	}

tryagain:
	n=read(STDIN_FILENO,buf,sizeof(buf));
	if(n<0){
		if(errno!=EWOULDBLOCK){
			perror("read /dev/tty error");
			exit(1);
		}else{
			write(STDOUT_FILENO,"try again\n",strlen("try again\n"));
			sleep(2);
			goto tryagain;
		}
	}

	write(STDOUT_FILENO,buf,n);
	close(fd);

	return 0;
}
