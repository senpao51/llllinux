#include <stdio.h>
#include <assert.h>
int romanTolnt(char* s)
{
	assert(s);
	int sum = 0;
	while(*s!='\0')
	{
		if(*s=='I'&&*(s+1)=='V')
		{
			sum=sum+4;
			s+=2;
			continue;
		}
		if(*s=='I'&&*(s+1)=='X')
		{
			sum =sum+9;
			s+=2;
			continue;
		}
		if(*s=='X'&&*(s+1)=='L')
		{
			sum =sum +40;
			s+=2;
			continue;
		}
		if(*s=='X'&&*(s+1)=='C')
		{
			sum=sum+90;
			s+=2;
			continue;
		}
		if(*s=='C'&&*(s+1)=='D')
		{
			sum =sum+400;
			s+=2;
			continue;
		}
		if(*s=='C'&&*(s+1)=='M')
		{
			sum =sum +900;
			s+=2;
			continue;
		}
//		switch(*s)
//		{
//			case'I':
//				{
//					sum+=1;
//					break;
///				}
//			case'V':
//				{
//					sum+=5;
//					break;
//				}
//			case'X':
//				{
//					sum+=10;
//					break;
//				}
//			case'L':
//				{
//					sum+=50;
//					break;
///				}
//			case'C':
//				{
//					sum+=100;
//					break;
//				}
//			case'D':
//				{
//					sum+=500;
//					break;
//				}
//			case'M':
//				{
//					sum+=1000;
//					break;
//				}
//			default:
//				{
//					break;
//				}
//		}
		if(*s=='I')
		{
			sum+=1;
		}
    	else if(*s=='V')
		{
			sum+=5;
		}
		else if(*s=='X')
		{
		sum+=10;
		}
		else if(*s=='L')
		{
			sum+=50;
		}
		else if(*s=='C')
		{
			sum+=100;
		}
		else if(*s=='D')
		{
			sum+=500;
		}
		else
		{
			sum+=1000;
		}
	s++;
	}
	return sum;
}
int main()
{
	char arr[]="MCMXCIV";
	int ret = romanTolnt(arr);
	printf("%d\n",ret);
	return 0;
}
