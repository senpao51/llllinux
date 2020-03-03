#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h> 
#include <sys/types.h>
int main()
{
	key_t k = ftok("/usr/bin/ls",0);
	if(k<0)
	{
		perror("ftok");
		return 1;
	}
	int shmid = shmget(k,4096,IPC_CREAT|0664);
	if(shmid<0)
	{
		perror("shmget");
		return 2;
	}
	char*str =(char*)shmat(shmid,NULL,0);
	int i = 0;
	while(i<26)
	{
		str[i] = 'A'+i;
		i++;
		str[i] = '\0';
		sleep(1);
	}
	shmdt(str);
	return 0;
}
