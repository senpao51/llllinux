#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "Util.h"
using namespace std;

int main()
{
	char* content_length = getenv("Content-Length"); 
	if(content_length != nullptr)
	{
		string str = content_length;
		string args;
		char c;
		int cl = Util::StringToInt(str);
		for(int i=0;i<cl;i++)
		{
			read(0,&c,1);
			args+=c;
		}
		cout<<args<<endl;
	}
	else
	{
		cout<<"get content length error!"<<endl;
	}
	return 0;
}
