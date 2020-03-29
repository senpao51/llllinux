#pragma once 
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
class RingQueue
{
private:
	void P(sem_t&t)
	{
		sem_wait(&t);
	}
	void V(sem_t&t)
	{
		sem_post(&t);
	}
public:
	RingQueue(int _cap = 20):cap(_cap),v(_cap)
	{
		sem_init(&c,0,0);
		sem_init(&p,0,cap);
	}
	void PushData(int& data)
	{
		static int pos_p = 0;
		P(p);
		v[pos_p] = data;
		V(c);
		pos_p++;
		pos_p%=cap;
	}
	void PopData(int& data)
	{
		static int pos_c = 0;
		P(c);
		data = v[pos_c];
		V(p);
		pos_c++;
		pos_c%=cap;

	}
	~RingQueue()
	{
		sem_destroy(&c);
		sem_destroy(&p);
	}
private:
	std::vector<int>v;
	int cap;
	sem_t c;
	sem_t p;	
};
