#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
int isValid(char* s)
{
	assert(s!=NULL);
	int sz = strlen(s);
	int i = 0;
	char*tmp =(char*)malloc(strlen(s));
	if(sz==0)
	{
		return 1;
	}
	if(sz/2==1||*s==')'||*s==']'||*s=='}')
	{
		return 0;
	}
	while(*s!='\0')
	{
		if(*s=='('||*s=='['||*s=='{')
		{
			tmp[i]=*s;
			i++;
			s++;
		}
		else
		{
			if(*s==tmp[i-1]+1||*s==tmp[i-1]+2)
			{
				i--;
				s++;
			}
			else
			{
				return 0;
			}
		}
	}
	if(i==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	char p[]="({[]({})})";
	int ret = isValid(p);
	if(ret ==0)
	{
		printf("false\n");
	}
	else
	{
		printf("true\n");
	}
	return 0;
}
