#include <stdio.h>
#include <unistd.h>
int main()
{
	const char* p ="abcdef";
	while(*p)
	{
		//printf("%c\n",*p);
		//printf("%c",*p);
		printf("%c\r",*p);
		fflush(stdout);
		p++;
		sleep(1);
	}
	return 0;
}

