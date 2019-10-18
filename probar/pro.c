#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
	char arr[101];
	char led[]="-/|\\";
	memset(arr,'\0',sizeof(arr));
	int i = 0;
	for(i=0;i<=100;i++)
	{
		printf("[%s][%d%%][%c]\r",arr,i,led[i%4]);
		fflush(stdout);
		usleep(100000);
		arr[i]='*';
	}
	printf("\n");
	return 0;
}
