#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

/*链表节点:产品*/
struct msg{
	int num;
	struct msg* next;
};

/*全局的一个头指针*/
struct msg* head;

/*创建全局锁和信号量*/
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;

void perr_exit(const char* str,int ret){
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}

/*消费者回调函数*/
void* consumer(void* arg){
	struct msg* mp;
	while(1){
		/*先加锁*/
		pthread_mutex_lock(&lock);
		/*当条件变量不满足时,解锁,并死循环等待*/
		while(head==NULL)
			pthread_cond_wait(&has_product,&lock);
		/*条件满足,被唤醒,加锁,进入临界区,从链表上摘下节点*/
		mp=head;
		head=mp->next;
		/*解锁*/
		pthread_mutex_unlock(&lock);

		printf("----Consumer=%lu,num=%d\n",pthread_self(),mp->num);
		free(mp);
		sleep(rand()%3);
	}
	return NULL;
}

/*生产者回调函数*/
void* producter(void* arg){
	struct msg* mp;
	while(1){
		/*生产一个节点*/
		mp=(struct msg*)malloc(sizeof(struct msg));
		mp->num=rand()%1000+1;
		printf("====Producter=%lu,num=%d\n",pthread_self(),mp->num);

		/*加锁,然后将产品放入临界区*/
		pthread_mutex_lock(&lock);
		mp->next=head;
		head=mp;
		/*解锁*/
		pthread_mutex_unlock(&lock);

		/*唤醒阻塞在条件变量上的线程*/
		pthread_cond_signal(&has_product);
		sleep(rand()%3);
	}

	return NULL;
}

int main(int argc,char* argv[]){

	srand(time(NULL));
	pthread_t pid,cid;
	/*创建生产者线程*/
	pthread_create(&pid,NULL,producter,NULL);
	/*创建多个消费者线程*/
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	/*回收两个子线程*/
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);

	return 0;
}