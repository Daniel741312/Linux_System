#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<dirent.h>

struct student{
	int id;
	char name[256];
	int age;
};

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

int main(int argc,char* argv[]){
	struct student stu;
	struct student* p;
	int fd=0;
	fd=open("temp",O_RDONLY);
	if(fd==-1)
		perr_exit("open error");

	p=(struct student*)mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
		perr_exit("mmap error");
	
	while(1){
		printf("id=%d,name=%s,age=%d\n",p->id,p->name,p->age);
		sleep(1);
	}

	munmap(p,sizeof(stu));
	close(fd);

	return 0;
}