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
	int i=0;
	for(i=0;i<5;++i){
		if(fork()==0)
			break;
	}

	if(i==5){
		sleep(5);
		printf("I'm parent\n");
	}
	else{
		sleep(i);
		printf("I'm %dth child\n",i+1);
	}

	sleep(1);
	return 0;
}
