#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	int n=0;
	char buf[10];

	/*Read the STDIN by a block way*/
	n=read(STDIN_FILENO,buf,sizeof(buf));
	if(n==-1){
		perror("read error");
		exit(1);
	}

	/*Write it to the STDOUT*/
	write(STDOUT_FILENO,buf,n);
	return 0;
}
