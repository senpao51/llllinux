#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 1024
static int quit = 1;
void Handler(struct pollfd pfds[],int num)
{
	for(int i=0;i<num;i++)
	{
		if(pfds[i].revents&POLLIN)
		{
			if(pfds[i].fd==0)
			{
				char buf[MAX];
				ssize_t s = read(0,buf,sizeof(buf));
				if(s>0)
				{
					buf[s-1]=0;
					if(strcmp(buf,"quit")==0)
					{
						quit = 0;
						break;
					}
					cout<<buf<<endl;
				}
			}
		}
	}
}
int main()
{
	struct pollfd pfds[1];
	pfds[0].fd = 0;
	pfds[0].events = POLLIN;
	pfds[0].revents = 0;
	while(quit)
	{
		cout<<"Please input info###"<<endl;
		fflush(stdout);
		switch(poll(pfds,1,-1))
		{
			case -1:
				cout<<"poll error!"<<endl;
				break;
			case 0:
				cout<<"time out!"<<endl;
				break;
			default:
				Handler(pfds,1);
				break;
		}
	}
	return 0;
}
