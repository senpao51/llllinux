#pragma once 
#include <iostream>
#include "common.h"
#include <string>
#include <pthread.h>
class Task
{
	public:
		Task()
		{}
		Task(int _sock):sock(_sock)
		{}
		~Task()
		{}
		void Run()
		{
			std::cout<<"Task id:"<<sock<<" pthread id:"<<pthread_self()<<std::endl;
			std::string msg;
			while(Pro::Recv(sock,msg))
			{
				std::cout<<"来自客户端的消息:"<<msg<<std::endl;
				Pro::Send(sock,msg);
			}	
			close(sock);
		}
	private:
		int sock;
};

