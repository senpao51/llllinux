#pragma once 

#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;


typedef void* (*Handler_t)(void*);

#define DEFAULT_NUM 5

class Task
{
public:
	Task()
	{}
	~Task()
	{}
public:
	void SetTask(int _sock,Handler_t _ht)
	{
		sock = _sock;
		ht = _ht;
	}
	void Run()
	{
		ht((void*)&sock);
	}
private:
	int sock;
	Handler_t ht;
};

class ThreadPool
{
public:
	ThreadPool(int _num = DEFAULT_NUM):num(_num)
	{
		pthread_mutex_init(&lock,nullptr);
		pthread_cond_init(&cond,nullptr);
	}
	void LockQueue()
	{
		pthread_mutex_lock(&lock);
	}
	void UnlockQueue()
	{
		pthread_mutex_unlock(&lock);
	}
	void Wait()
	{
		pthread_cond_wait(&cond,&lock);
	}
	void Wakeup()
	{
		pthread_cond_signal(&cond);
	}
	bool QueueIsEmpty()
	{
		return q.empty();
	}
	void Push(Task& t)
	{
		LockQueue();
		q.push(t);
		UnlockQueue();
		Wakeup();
	}
	Task Pop()
	{
		Task t = q.front();
		q.pop();
		return t;
	}
	static void* Routine(void* arg)
	{
		pthread_detach(pthread_self());
		ThreadPool *tp = (ThreadPool*)arg;
		while(true)
		{
			tp->LockQueue();
			while(tp->QueueIsEmpty())
			{
				tp->Wait();
			}
			Task t = tp->Pop();
			tp->UnlockQueue();
			t.Run();
		}
	}
	void InitThreadPool()
	{
		for(int i=0;i<num;i++)
		{
			pthread_t tid;
			pthread_create(&tid,nullptr,Routine,this);
		}
	}
	~ThreadPool()
	{
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&cond);
	}
private:
	int num;
	pthread_mutex_t lock;
	pthread_cond_t cond;
	queue<Task>q;
};
