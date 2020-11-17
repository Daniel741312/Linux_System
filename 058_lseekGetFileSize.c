#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char* argv[]){

	int fd=open(argv[1],O_RDWR);
	if(fd==-1){
		perror("open error");
		exit(1);
	}

	/*From the EOF*/
	int size=lseek(fd,0,SEEK_END);
	printf("The file's size:%d\n",size);

	close(fd);
	return 0;
}
