#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>

#define PATH_LEN 256

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

void fetchdir(const char* dir,void(*fcn)(char*)){
	char name[PATH_LEN];
	struct dirent* sdp;
	DIR* dp;

	if((dp=opendir(dir))==NULL){
		fprintf(stderr,"fetchdir:can't open %s\n",dir);
		return;
	}

	while((sdp=readdir(dp))!=NULL){
		if((strcmp(sdp->d_name,".")==0)||(strcmp(sdp->d_name,"..")==0))
			continue;
		
		if(strlen(dir)+strlen(sdp->d_name)+2>sizeof(name)){
			fprintf(stderr,"fetchdir:name %s %s is too long\n",dir,sdp->d_name);
		}else{
			sprintf(name,"%s/%s",dir,sdp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dp);
}

void isFile(char* name){
	struct stat sbuf;
	if(stat(name,&sbuf)==-1){
		fprintf(stderr,"isFile:can't access %s\n",name);
		exit(1);
	}
	if((sbuf.st_mode&S_IFMT)==S_IFDIR){
		fetchdir(name,isFile);
	}
	printf("%ld\t\t%s\n",sbuf.st_size,name);
}

int main(int argc,char* argv[]){

	if(argc==1)
		isFile(".");
	else{
		while(--argc>0)
			isFile(*++argv);
	}

	return 0;
}