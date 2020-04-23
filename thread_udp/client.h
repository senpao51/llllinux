#pragma once 
#include <iostream>
#include "common.h"

class Client
{
	public:
		Client(std::string _ip,int _port):ip(_ip),port(_port),sockfd(-1)
		{}
		~Client()
		{
			if(sockfd>=0)
			{
				close(sockfd);
			}
		}
	public:
		void InitClient()
		{
			sockfd = Pro::Sock();
			Pro::Connect(sockfd,ip,port);
		}
		void Run()
		{
			while(1)
			{
				std::string input;
				std::cout<<"请输入:";
				std::cin>>input;
				Pro::Send(sockfd,input);	
				Pro::Recv(sockfd,input);
				std::cout<<"来自服务器的回显："<<input<<std::endl;
			}
		}
	private:
		int sockfd;
		std::string ip;
		int port;
};
