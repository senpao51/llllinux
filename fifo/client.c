#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	int fifo = mkfifo("file",0664);
	if(fifo<0)
	{
		perror("mkfifo");
		return 1;
	}
	int fd = open("file",O_WRONLY);
	if(fd<0)
	{
		perror("open");
		return 2;
	}
	char buf[1024];
	while(1)
	{
		printf("Please input:\n");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf));
		if(s>0)
		{
			buf[s] = '\0';
			write(fd,buf,sizeof(buf));
		}
		else
			break;
	}
	close(fd);
	return 0;
}
