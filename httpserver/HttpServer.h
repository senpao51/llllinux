#pragma once 
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include "Sock.h"
#include "Pro.h"
#include "ThreadPool.h"
#include "Log.h"
using namespace std;


#define DEFAULT_PORT 8080
class HttpServer
{
public:
	HttpServer(int _port = DEFAULT_PORT):port(_port),listen_sock(-1),tp(nullptr)
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
		signal(SIGPIPE,SIG_IGN);
		tp = new ThreadPool();
		tp->InitThreadPool();
	}
	void Run()
	{
		while(1)
		{
			LOG(NORMAL,"server start successfully!");
			int sock = Sock::Accept(listen_sock);
			if(sock>=0)
			{
				LOG(NORMAL,"get a new link!");
				Task t;
				t.SetTask(sock,Entry::HandlerRequest);
				tp->Push(t);
			}
		}
	}
private:
	int listen_sock;
	int port;
	ThreadPool *tp;
};
