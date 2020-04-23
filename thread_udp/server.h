#pragma once 
#include <iostream>
#include "common.h"
#include "ThreadPool.h"
class Server
{
	public:
		Server(std::string _ip,int _port):ip(_ip),port(_port),sockfd(-1),tp(10)
		{}
		~Server()
		{
			if(sockfd>=0)
			{
				close(sockfd);
			}
		}
		void InitServer()
		{
			sockfd = Pro::Sock();
			Pro::Bind(sockfd,ip,port);
			Pro::Listen(sockfd,DEAFAULT_BACKLOG);
			tp.InitThreadPool();
		}
		void Run()
		{
			while(1)
			{
				int newsock = Pro::Accept(sockfd);
				if(newsock>0)
				{
					std::cout<<"新连接加入"<<std::endl;
					Task t(newsock);
					tp.PushTask(t);
				}
			}
		}
	private:
		int sockfd;
		std::string ip;
		int port;
		ThreadPool tp;
};
