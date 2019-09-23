#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
char* longest(char** str,int sz)
{
	assert(str);
	int i = 0;
	char* head= *(str+0);
	char* tail= *(str+1);
	char* cmp = NULL;
	char* tmp = *(str+1);
	char* ret = NULL;
	if(sz==0)
	{
		return " ";
	}
	if(sz==1)
	{
		return *(str+0);
	}
	while(*head==*tail)
	{
		head++;
		tail++;
	}
	for(i=2;i<sz;i++)
	{
		head = *(str+1);
		cmp = *(str+i);
		while(*head==*cmp)
		{
			head++;
			cmp++;
		}
		if(head<tail)
		{
			tail = head;
		}
		if(tail==tmp)
		{
			return " ";
		}
	}
	ret = (char*)malloc(sizeof(char)*(tail-tmp+1));
	for(i=0;i<tail-tmp;i++)
	{
		*(ret+i)= *(tmp+i);
	}
	*(ret+(tail-tmp))= '\0';
	return ret;
}
int main()
{
	char*p[]={"flower","float","flow","flight"};
	int sz = sizeof(p)/sizeof(p[0]);
	char*ret = longest(p,sz);
	printf("%s\n",ret);
	return 0;
}


