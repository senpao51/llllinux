#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
	execl("/bin/ls","ls","-a","-l",nullptr);
	cout<<"hello world"<<endl;
	return 0;
}
