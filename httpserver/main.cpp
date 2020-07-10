#include "HttpServer.h"

#include "Log.h"
void Usage(string msg)
{
	cout<<msg<<" port"<<endl;
}
//./httpserver 8080
int main(int argc,char*argv[])
{
	HttpServer* svr = nullptr;
	if(argc==1)
	{
		LOG(NORMAL,"create successfully,use default port!");
		svr = new HttpServer();
	}
	else if(argc==2)
	{
		LOG(NORMAL,"create successfully,use assign port!");
		svr = new HttpServer(atoi(argv[1]));
	}
	else
	{
		Usage(argv[0]);
		exit(ARG_ERROR);
	}
	svr->InitHttpServer();
	svr->Run();
	delete svr;
	return 0;
}
