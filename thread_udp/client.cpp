#include "client.h"
void method(char*msg)
{
	std::cout<<msg<<" server ip, server port"<<std::endl;
}
int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		method(argv[0]);
	}
	Client ct(argv[1],atoi(argv[2]));
	ct.InitClient();
	ct.Run();
	return 0;
}
