#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
	cout<<"pid:"<<getpid()<<" "<<"ppid:"<<getppid()<<endl;
	sleep(3);
	pid_t id = fork();
	if(id==0)
	{
		while(1)
		{
			cout<<"child "<<"pid:"<<getpid()<<" "<<"ppid:"<<getppid()<<endl;
			sleep(1);
		}
	}
	else if(id>0)
	{
		while(1)
		{
			cout<<"father "<<"pid:"<<getpid()<<" "<<"ppid:"<<getppid()<<endl;
			sleep(5);
		}
	}
	else
	{
		//error
	}
	return 0;
}
