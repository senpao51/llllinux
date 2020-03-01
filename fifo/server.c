#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd = open("file",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return 1;
	}
	char buf[1024];
	while(1)
	{
		ssize_t s = read(fd,buf,sizeof(buf));
		if(s>0)
		{
			buf[s] = '\0';
			printf("client success!\n");
			printf("%s",buf);
		}
		else
			break;
	}
	close(fd);
	return 0;
}
