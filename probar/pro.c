#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int i = 0;
	char bar[101];
	char lab[]="|/-\\";
	memset(bar,'\0',sizeof(bar));
	for(i=0;i<=100;i++)
	{
		printf("[%-100s][%d\%][%c]\r",bar,i,lab[i%4]);
		fflush(stdout);
		bar[i]='#';
		usleep(100000);
	}
	printf("\n");
	return 0;
}

