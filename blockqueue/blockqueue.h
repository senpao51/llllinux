#pragma once
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
class BlockQueue
{
private:
	bool IsFull()
	{
		return q.size()==capacity;
	}
	bool IsEmpty()
	{
		return q.size()==0;
	}
	void ConsumerWait()
	{
		pthread_cond_wait(&c,&lock);
	}
	void ProductorWait()
	{
		pthread_cond_wait(&p,&lock);
	}
	void BlockQueueLock()
	{
		pthread_mutex_lock(&lock);
	}
	void BlockQueueUnlock()
	{
		pthread_mutex_unlock(&lock);
	}
public:
	BlockQueue(int _capacity = 3):capacity(_capacity)
	{
		pthread_mutex_init(&lock,nullptr);
		pthread_cond_init(&c,nullptr);
		pthread_cond_init(&p,nullptr);
	}
	void PushData(int data)
	{
		BlockQueueLock();
		while(IsFull())
		{
			pthread_cond_signal(&c);
			ProductorWait();
		}
		q.push(data);
		BlockQueueUnlock();
	}
	void PopData(int &data)
	{
		BlockQueueLock();
		while(IsEmpty())
		{
			pthread_cond_signal(&p);
			ConsumerWait();
		}
		data = q.front();
		q.pop();
		BlockQueueUnlock();
	}
	~BlockQueue()
	{
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&c);
		pthread_cond_destroy(&p);
	}
private:
	std::queue<int>q;
	int capacity;
	pthread_mutex_t lock;
	pthread_cond_t c;
	pthread_cond_t p;
};
