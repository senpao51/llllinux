#pragma once 
#include "Log.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;
class HttpRequest
{
private:
	string request_line;
	string request_header;
	string blank;
	string request_text;
};
class HttpResponse
{
private:
	string response_line;
	string response_header;
	string blank;
	string response_text;
};
class Connect
{
public:
	Connect(int _sock):sock(_sock)
	{}
	//1 \r
	//2 \r\n
	//3 \n
	//一次读一个字符
	int RecvLine(string &line)
	{
		char c = 'A';
		while(c!='\n')
		{
			ssize_t s = recv(sock,&c,1,0);
			if(s>0)
			{
				if(c=='\r')
				{
					recv(sock,&c,1,MSG_PEEK);//窥探底层数据，并不拿走底层数据
					if(c=='\n')
						recv(sock,&c,1,0);
					else
						c = '\n';
				}
				line += c;
			}
			else
			{
				LOG(ERROR,"recv error!");
			}
		}
		return line.size();
	}
	void RecvHttpRequest(HttpRequest*& rq)
	{}
	~Connect()
	{}
private:
	int sock;
};
class Entry
{
public:
	static void* HandlerRequest(void*arg)
	{
		int* sock = (int*)arg;
		HttpRequest* rq = new HttpRequest();
		HttpResponse* rp = new HttpResponse();
		Connect* con = new Connect(*sock);
		con->RecvHttpRequest(rq);
		//recv request
		//解析
		//制作响应
		//发送响应
		delete rq;
		delete rp;
		delete con;
	}
};
