#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
void lock()
{
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}
void unlock()
{
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}
void*one(void*arg)
{
	char*msg = (char*)arg;
	cout<<msg<<endl;
	sleep(1);
	pthread_mutex_unlock(&lock1);
}
void*two(void*arg)
{
	pthread_mutex_lock(&lock1);
	char*msg = (char*)arg;
	cout<<msg<<endl;
	sleep(2);
	pthread_mutex_unlock(&lock2);
}
void*three(void*arg)
{
	pthread_mutex_lock(&lock2);
	char*msg = (char*)arg;
	cout<<msg<<endl;
}
int main()
{
	pthread_mutex_init(&lock1,nullptr);
	pthread_mutex_init(&lock2,nullptr);
	lock();
	pthread_t t1,t2,t3;
	pthread_create(&t3,nullptr,three,(void*)"three");
	pthread_create(&t1,nullptr,one,(void*)"one");
	pthread_create(&t2,nullptr,two,(void*)"two");
	pthread_join(t1,nullptr);
	pthread_join(t2,nullptr);
	pthread_join(t3,nullptr);
	unlock();
	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	return 0;
}
