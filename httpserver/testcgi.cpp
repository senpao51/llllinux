#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "Util.h"
using namespace std;
void GetSubString(string str,int& x,int& y)
{
	bool flag = true;
	auto start = str.find("=");
	auto end = str.find("&");
	if(start!=string::npos && end!=string::npos)
	{
		string sub = str.substr(start+1,end-start+1);
		x = Util::StringToInt(sub);
	}
	else
		flag = false;
	auto pos = str.rfind("=");
	if(pos!=string::npos)
	{
		string sub = str.substr(pos+1);
		y = Util::StringToInt(sub);
	}
	else
		flag = false;
	if(!flag)
		cout<<"args error!"<<endl;
}
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
		cout<<"<html><h3>";
		int x,y;
		GetSubString(args,x,y);
		cout<<"data1 + data2 = "<< x + y <<"<br/>"<<endl;
		cout<<"data1 - data2 = "<< x - y <<"<br/>"<<endl;
		cout<<"data1 * data2 = "<< x * y <<"<br/>"<<endl;
		if(y!=0)
			cout<<"data1 / data2 = "<<  x/y <<endl;
		else
			cout<<"div zero! error!"<<endl;
		cout<<"</h3></html>"<<endl;
	}
	else
	{
		cout<<"get content length error!"<<endl;
	}
	return 0;
}
