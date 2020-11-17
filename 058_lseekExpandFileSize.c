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

	/*Set the file cursor at EOF+110*/
	int size=lseek(fd,110,SEEK_END);
	printf("The file's size:%d\n",size);

	/*Write a null char to really change the file size*/
	write(fd,"\0",1);

	close(fd);
	return 0;
}
