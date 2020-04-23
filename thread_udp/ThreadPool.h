#pragma once
#include <iostream>
#include <pthread.h>
#include "common.h"
#include <queue>
#include "Task.h"

class ThreadPool
{
	public:
		ThreadPool(int _num = 10):num(_num)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		bool ThreadPoolEmpty()
		{
			return q.empty();
		}
		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}
		void UnlockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void ThreadWakeUp()
		{
			pthread_cond_signal(&cond);
		}
		void PushTask(Task&t)
		{
			LockQueue();
			q.push(t);
			UnlockQueue();
			ThreadWakeUp();
		}
		void PopTask(Task&t)
		{
			t = q.front();
			q.pop();
		}
		static void* TaskRoutine(void*arg)
		{
			pthread_detach(pthread_self());
			ThreadPool*tp = (ThreadPool*)arg;
			while(1)
			{
				Task t;
				tp->LockQueue();
				while(tp->ThreadPoolEmpty())
				{
					tp->ThreadWait();
				}
				tp->PopTask(t);
				tp->UnlockQueue();
				t.Run();
			}
		}
		void InitThreadPool()
		{
			for(int i=0;i<num;i++)
			{
				pthread_t tid;
				pthread_create(&tid,nullptr,TaskRoutine,(void*)this);
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
		std::queue<Task>q;
};
