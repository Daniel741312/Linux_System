#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	int fd=0;
	int n=0;
	char msg[]="It's a lseek test\n";
	char c;

	fd=open("./lseek.txt",O_CREAT|O_RDWR,0644);
	if(fd==-1){
		perror("open error");
		exit(1);
	}

	write(fd,msg,strlen(msg));

	/*Set the file cursor back to the begin*/
	lseek(fd,0,SEEK_SET);

	while((n=read(fd,&c,1))){
		if(n==-1){
			perror("read error");
			exit(1);
		}
		write(STDOUT_FILENO,&c,n);
	}

	close(fd);
	return 0;
}
