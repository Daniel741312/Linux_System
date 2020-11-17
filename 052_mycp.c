#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	char buf[1024];
	int n=0;

	/*Src file*/
	int fd1=open(argv[1],O_RDONLY);
	if(fd1==-1){
		perror("open argv1 error");
		exit(1);
	}

	/*Dst file*/
	int fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd2==-1){
		perror("open argv2 error");
		exit(1);
	}

	/*Read from the src file*/
	while((n=read(fd1,buf,sizeof(buf)))!=0){
		if(n<0){
			perror("open argv2 error");
			break;
		}
		/*Write to the dst file*/
		write(fd2,buf,n);
	}

	close(fd1);
	close(fd2);
	return 0;
}
