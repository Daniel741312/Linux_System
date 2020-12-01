#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int counter;

/*创建一把全局锁*/
pthread_rwlock_t rwlock;

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

/*写线程回调函数*/
void* th_write(void* arg){
	int t=0;
	int i=(int)arg;
	while(1){
		/*加写锁*/
		pthread_rwlock_wrlock(&rwlock);
		t=counter;
		usleep(1000);
		printf("----Write:i=%d,tid=%lu,conter=%d,++conter=%d\n",i,pthread_self(),t,++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(10000);
	}
	return NULL;
}

/*读线程回调函数*/
void* th_read(void* arg){
	int i=(int)arg;
	while(1){
		/*加读锁*/
		pthread_rwlock_rdlock(&rwlock);
		printf("Read:i=%d,tid=%lu,conter=%d\n",i,pthread_self(),counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(2000);
	}
	return NULL;
}

int main(int argc,char* argv[]){
	int i=0;
	pthread_t tid[8];

	/*在主线程中初始化读写锁*/
	pthread_rwlock_init(&rwlock,NULL);

	/*创建3个写线程*/
	for(i=0;i<3;++i)
		pthread_create(tid+i,NULL,th_write,(void*)i);

	/*创建5个读线程*/
	for(i=0;i<5;++i)
		pthread_create(tid+3+i,NULL,th_read,(void*)i);

	/*回收8个子线程*/
	for(i=0;i<8;++i)
		pthread_join(tid[i],NULL);

	/*销毁读写锁*/
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
