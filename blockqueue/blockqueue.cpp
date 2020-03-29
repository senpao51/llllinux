#include "blockqueue.h"
#include <iostream>
using namespace std;
void* productor(void*arg)
{
	BlockQueue*bq = (BlockQueue*)arg;
	srand((unsigned int)time(nullptr));
	while(1)
	{
		int data = rand()%100+1;//产生随机数
		bq->PushData(data);
		cout<<"product a number:"<<data<<endl;
	}
}
void* consumer(void*arg)
{
	BlockQueue*bq = (BlockQueue*)arg;
	int data;
	while(1)
	{
		bq->PopData(data);
		cout<<"consume a number:"<<data<<endl;
	//	sleep(1);
	}
}
int main()
{
	BlockQueue*bq = new BlockQueue;
	pthread_t c,p;
	pthread_create(&p,nullptr,productor,(void*)bq);
	pthread_create(&c,nullptr,consumer,(void*)bq);
	pthread_join(p,nullptr);
	pthread_join(c,nullptr);
	delete bq;
	return 0;
}
