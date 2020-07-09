#pragma once 
#include <iostream>
#include "Sock.h"
#include "Log.h"
using namespace std;


#define DEFAULT_PORT 8080
class HttpServer
{
public:
	HttpServer(int _port = DEFAULT_PORT):port(_port),listen_sock(-1)
	{}
	~HttpServer()
	{
		if(listen_sock>=0)
		{
			close(listen_sock);
		}
	}
public:
	void InitHttpServer()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock,port);
		Sock::Listen(listen_sock);
	}
	void Run()
	{
		while(1)
		{
			LOG(NORMAL,"test");
			sleep(1);
		//	int sock = Sock::Accept(listen_sock);
		//	if(sock>0)
		//	{
		//		LOG(NORMAL,"get a new link!");
		//		sleep(1);
		//	}
		}
	}
private:
	int listen_sock;
	int port;
};
