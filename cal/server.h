#pragma once 
#include "common.h"
#include "type.h"
class Server
{
	public:
		Server(int _port):port(_port),sock(-1)
		{}
		~Server()
		{
			if(sock>=0)
			{
				close(sock);
			}
		}
		void InitServer()
		{
			sock = Pro::Sock();
			Pro::Bind(sock,port);
			Pro::Listen(sock,5);
		}
		void ServerIO(int newsock)
		{
			while(1)
			{
				request_t rq;
				response_t rp;
				memset(&rq,0,sizeof(rq));
				memset(&rp,0,sizeof(rp));
				ssize_t s = read(newsock,&rq,sizeof(rq));
				if(s>0)
				{	
					std::cout<<"client#"<<rq.x<<" "<<rq.op<<" "<<rq.y<<std::endl;
					switch(rq.op)
					{
						case '+':
							rp.result = rq.x+rq.y;
							break;
						case '-':
							rp.result = rq.x-rq.y;
							break;
						case '*':
							rp.result = rq.x*rq.y;
							break;
						case '/':
							{
								if(rq.y==0)
									rp.status = -1;
								else
									rp.result = rq.x/rq.y;
							}
							break;
						case '%':
							{
								if(rq.y==0)
									rp.status = -2;
								else
									rp.result = rq.x%rq.y;
							}
							break;
						default:
							rp.status = -3;
							break;
					}
					write(newsock,&rp,sizeof(rp));
				}
			}

		}
		void Run()
		{
			while(1)
			{
				signal(SIGCHLD,SIG_IGN);
				int newsock = Pro::Accept(sock);
				if(newsock>0)
				{
					pid_t id = fork();
					if(id==0)
					{
						close(sock);
						std::cout<<"新连接加入"<<std::endl;
						ServerIO(newsock);
						exit(0);
					}
				}
				close(newsock);
			}
		}
	private:
		int sock;
		int port;
};
