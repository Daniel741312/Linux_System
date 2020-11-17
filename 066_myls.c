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
	DIR* dp;
	struct dirent* sdp;
	dp=opendir(argv[1]);
	if(dp==NULL)
		perr_exit("opendir error");

	while((sdp=readdir(dp))!=NULL){
		if(!strcmp(sdp->d_name,"."))
			continue;
		if(!strcmp(sdp->d_name,".."))
			continue;
		printf("%s\n",sdp->d_name);
	}
	printf("\n");

	closedir(dp);
	return 0;
}
