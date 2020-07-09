#pragma once 
#include "HttpServer.h"
#include "Log.h"
#include <iostream>
#include <string>
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

	void RecvHttpRequest(HttpRequest& rq)
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
		int sock = (int)arg;
		HttpRequest* rq = new HttpRequest();
		HttpResponse* rp = new HttpResponse();
		Connect* con = new Connect(sock);
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
