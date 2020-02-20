#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;
int main()
{
	string s;	
	while(1)
	{
		cout<<"XXX@HOSTNAME shell# ";
		getline(cin,s);
		char*str = (char*) s.c_str();
		char*buf[20] = {0};
		int i =0;
		int len = strlen(str);
		pid_t id = fork();
		if(id==0)
		{
			while(*str!='\0')
			{
				char*m_str = str;
				while(!isspace(*str)&&len!=0)
				{
					str++;
					len--;
				}
				*str='\0';
				buf[i++] = m_str;
				if(len>0)
				{	
					str++;
					len--;					}
				}
			buf[i] = NULL;
			execvp(buf[0],buf);
		}
		else if(id>0)
		{
			waitpid(id,NULL,0);
		}	
		else
		{
			cout<<"error"<<endl;
		}
	}
	return 0;
}
