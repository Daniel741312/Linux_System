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
#include<signal.h>

void perr_exit(const char* str){
	perror(str);
	exit(1);
}

void catch_child(int signum){
	pid_t wpid;

	/*
		*这里要用循环回收多个子进程:
		*如果只简单的调用一次wait,会造成当多个子进程同时发信号时,父进程只能响应一次回收过程,
		*而设置了while相当于自动提醒父进程要检查还有没有未回收的子进程,知道都回收完了,返回-1.
	*/
	while((wpid=wait(NULL))!=-1){
		printf("Catch child:%d\n",wpid);
	}
	return;
}

int main(int argc,char* argv[]){
	pid_t pid;
	int i=0;

	/*
		*那么如何解决父进程注册信号捕捉函数时子进程无法回收的问题呢(下面sleep(1)的问题)?
		*先设置信号屏蔽,将子进程发来的信号屏蔽在未决信号集上,
		*后面一旦信号集被打开,父进程就会处理未决信号集中的信号,
		*进入到信号捕捉函数,while(wait(NULL))自动提醒父进程检查回收子进程
	*/
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,NULL);

	for(i=0;i<15;++i)
		if((pid=fork())==0)
			break;
		
	if(i==15){
		struct sigaction act,oldact;
		act.sa_handler=catch_child;
		sigemptyset(&(act.sa_mask));
		act.sa_flags=0;
		/*	
			*这里设置sleep(1)只是为了模拟如果父进程注册信号的时间很长,
			*在这期间子进程已经死亡而发送的信号没有被父进程响应.
		*/
		sleep(1);
		sigaction(SIGCHLD,&act,&oldact);

		/*此处将阻塞解除,父进程能拿到SIGCHLD信号*/
		sigprocmask(SIG_UNBLOCK,&set,NULL);

		printf("I'm parent,pid=%d\n",getpid());
		while(1);
	}
	else
		printf("I'm child,pid=%d\n",getpid());

	return 0;
}
