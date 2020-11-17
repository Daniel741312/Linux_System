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

	/*Reopen the tty by a nonblock way*/
	fd=open("/dev/tty",O_RDONLY|O_NONBLOCK);
	if(fd<0){
		perror("open /dev/tty error");
		exit(1);
	}

tryagain:
	/*Read from fd*/
	n=read(fd,buf,sizeof(buf));
	/*If error*/
	if(n<0){
		/*If error is not coused by EWOULDBLOCK,which means fatal error*/
		if(errno!=EWOULDBLOCK){
			perror("read /dev/tty error");
			exit(1);
		}else{
			/*If the error is coused by EWOULDBOLCK,which means the file(device) is empty,just try again*/
			write(STDOUT_FILENO,"try again\n",strlen("try again\n"));
			sleep(2);
			goto tryagain;
		}
	}

	/*If no error,which means the file(device) has data,then write it to the STDOUT*/
	write(STDOUT_FILENO,buf,n);
	close(fd);

	return 0;
}
