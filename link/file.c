#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	printf("hello world!\n");
	return 0;
}
//int main()
//{
//	int fd = open("file.txt",O_WRONLY|O_CREAT|O_,0664);
//	if(fd<0)
//	{
//		printf("open error!\n");
//		return 1;
//	}
//	const char*buf = "hello world!\n";
//	dup2(fd,1);
//	write(1,buf,strlen(buf));
//	write(fd,buf,strlen(buf));
//	return 0;
//}
//int main()
//{
//	close(1);
//	int fd = open("file.txt",O_WRONLY|O_CREAT,0664);
//	if(fd<0)
//	{
//		printf("open error!\n");
//		return 1;
//	}
//	printf("fd:%d\n",fd);
//	fflush(stdout);
//	//write(fd,"hello world!\n",10);
//	close(fd);
//	return 0;
//}
