#include "ringqueue.h"
void* productor(void*arg)
{
	RingQueue*rq = (RingQueue*)arg;
	srand((unsigned long)time(nullptr));
	while(true)
	{
		int data = rand()%100+1;
		rq->PushData(data);
		std::cout<<"productor number is:"<<data<<std::endl;
		sleep(1);
	}
}
void* consumer(void*arg)
{
	RingQueue*rq = (RingQueue*)arg;
	while(true)
	{
		int data = 0;
		rq->PopData(data);
		std::cout<<"consumer number is:"<<data<<std::endl;
		sleep(1);
	}
}
int main()
{
	RingQueue*rq = new RingQueue(5);
	pthread_t c,p;
	pthread_create(&p,nullptr,productor,rq);
	pthread_create(&c,nullptr,consumer,rq);
	pthread_join(p,nullptr);
	pthread_join(c,nullptr);
	delete rq;
	return 0;
}
