#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
	char bar[101];
	int i = 0;
	char arr[]="/-\\|";
	memset(bar,'\0',sizeof(bar));
	for(i=0;i<=100;i++)
	{
		printf("\033[32m [%-100s]",bar);
		printf("\033[33m [%d%%]",i);
		printf("\033[35m [%c]\r",arr[i%4]);
		bar[i]='*';
		fflush(stdout);
		usleep(100000);
	}
	printf("\n");
	return 0;
}
