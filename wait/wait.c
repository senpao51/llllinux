#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
	pid_t id = fork();
	if(id==0)
	{
		//child
		printf("I am a child pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(1);
		exit(1);
	}
	else if(id>0)
	{
		int status=0;
		int ret =0;
		ret = waitpid(-1,&status,0);//阻塞等待
//		do
//		{
//			ret = waitpid(-1,&status,WNOHANG);
//			if(ret==0)
//			{
//				printf("child is running!\n");
//			}
//			sleep(1);
//		}while(ret==0);//非阻塞等待
		if(WIFEXITED(status))
		{
			printf("wait success,exit code=%d\n",WEXITSTATUS(status));
		}
		else
		{
			printf("wait defeat!\n");
		}
	}
//	int status = 0;
//	int ret = wait(&status);
//	printf("ret=%d\n",ret); wait失败返回-1 ，没有子进程。
//	pid_t id = fork();
//	if(id==0)
//	{
//		//child 
//		printf("I am a child pid:%d ppid:%d\n",getpid(),getppid());
//		sleep(1);
//	    exit(86);
//	}
//	else if(id>0)
//	{
//		int status=0;
//		int ret = wait(&status);
//		if(ret==-1)
//		{
//			printf("wait error!\n");
//		}
//		if(ret>0)
//		{
//			if(WIFEXITED(status))//判断子进程是否正常退出，正常退出返回非0值，
//			{
//				printf("exit code = %d\n",WEXITSTATUS(status));//获取子进程的退出码
//			}
//			printf("ret=%d\n",ret);
//		}
//	}
//	else
//	{
//		return;
//	}
	return 0;
}
