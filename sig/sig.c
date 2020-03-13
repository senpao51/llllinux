#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void printpendingmap(sigset_t* p)
{
	int i =0;
	for(i = 1;i<=31;i++)
	{
		if(sigismember(p,i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}
void handler(int sig)
{
	printf("handler success.sig:\n",sig);
}
int main()
{
	sigset_t block,oblock;
	sigemptyset(&block);
	sigaddset(&block,2);
	signal(2,handler);
	sigprocmask(SIG_BLOCK,&block,&oblock);
	int count = 0;
	while(1)
	{
		sigset_t pend;
		sigpending(&pend);
		printpendingmap(&pend);
		count++;
		sleep(1);
		if(count==5)
		{
			sigprocmask(SIG_SETMASK,&oblock,NULL);
			printf("blockmap is empty!\n");
			break;
		}
	}
}
