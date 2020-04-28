#include "server.h"
void method(char*msg)
{
	std::cout<<msg<<"server port"<<std::endl;
}
int main(int argc,char*argv[])
{
	if(argc!=2)
	{
		method(argv[0]);
	}
	Server sv(atoi(argv[1]));
	sv.InitServer();
	sv.Run();
	return 0;
}
