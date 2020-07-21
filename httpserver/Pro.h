#pragma once 
#include "Log.h"
#include "Util.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <strings.h>
#include <unordered_map>
using namespace std;

#define DEFAULT_ROOT "./page"
#define DEFAULT_PAGE "index.html"



class HttpRequest
{
public:
	HttpRequest():blank("\n"),path(DEFAULT_ROOT),cgi(false)
	{}
	~HttpRequest()
	{}
public:
	bool MethodIsOK()//判断方法是否为GET或POST
	{
		if(strcasecmp(method.c_str(),"GET")==0||strcasecmp(method.c_str(),"POST")==0)
			return true;
		return false;
	}
	bool MethodIsGet()//判断方法是否为GET
	{
		if(strcasecmp(method.c_str(),"GET")==0)
			return true;
		return false;
	}
	bool MethodIsPost()//判断方法是否为POST
	{
		if(strcasecmp(method.c_str(),"POST")==0)
			return true;
		return false;
	}
	bool PathIsLegal()
	{
		//stat
		struct stat st;
		if(stat(path.c_str(),&st)==0)
		{
			//请求资源存在
			if(S_ISDIR(st.st_mode))//判断是否是目录
			{
				if(path[path.size()-1]!='/')
					path+='/';
				path += DEFAULT_PAGE;
			}
		//	else if()// 判断是否具有可执行权限 cgi程序必须具有可执行权限
		//	{
		//		//使用cgi的场合：1.POST方法 2.GET方法带参数 3.请求的资源具有可执行权限
		//	}
		}
		else
		{
			//请求资源不存在
		}
	}
public:
	void SetRequestLine(string& line)//设置请求行
	{
		request_line = line;
	}
	void SetRequestHeader(string& header)//设置请求报头
	{
		request_header = header;
	}
	void SetRequestText(string& text)
	{
		request_text = text;
	}
	void SetRequestPath()//当方法为POST方法时，path就为url
	{
		path += url;
	}
	void SetCgi()
	{
		cgi = true;
	}
public:
	int GetContentLength()
	{
		auto it = header_map.find("Content-Length");
		if(it==header_map.end())
		{
			LOG(WARNING,"request_text is not exist!");
			return OTHER;
		}
		return Util::StringToInt(it->second);
	}
public:
	void DetachUrl()
	{
		//url = 资源路径path+ ? +参数parameter(有可能不存在)
		auto p = url.find('?');
		if(p == string::npos)
		{
			//不带参数
			path += url;
		}
		else
		{
			//带参数
			path += url.substr(0,p);
			parameter = url.substr(p+1);
			cgi = true;
		}

	}
	void DetachRequestLine()//分离请求行   方法  url  版本
	{
		stringstream ss(request_line);
		ss>>method>>url>>version;
		cout<<"method = "<<method<<endl;
		cout<<"url =  "<<url<<endl;
		cout<<"version = "<<version<<endl;
	}
	void DetachRequestHeader()//分离请求报头
	{
		auto pos = request_header.find('\n');
		auto start = 0;
		while(pos!=string::npos)
		{
			string str = request_header.substr(start,pos-start);
			Util::MakeKV(header_map,str);
			start = pos+1;
			pos = request_header.find('\n',pos+1);
		}
	}
	void show()
	{
		cout<<"###############################"<<endl;
		cout<<"reline = "<<request_line;
		cout<< "request_header = "<<request_header;
		cout<< "blank = "<<blank;
		cout<<"request = "<<request_text<<endl;
		cout<<"method = "<<method<<endl;
		cout<<"url = "<<url<<endl;// path+ ? +parameter
		cout<<"version = "<<version<<endl;
		cout<<"path = "<<path<<endl;//资源路径  
		cout<<"parameter = "<<parameter<<endl;//参数
		cout<<"###############################"<<endl;
	}
private:
	string request_line;
	string request_header;
	string blank;
	string request_text;
	string method;
	string url;// path+ ? +parameter
	string version;
	string path;//资源路径  
	string parameter;//参数
	unordered_map<string,string>header_map;
	bool cgi;
};
class HttpResponse
{
private:
	string response_line;
	string response_header;
	string blank;
	string response_text;
};
class Connect
{
public:
	Connect(int _sock):sock(_sock)
	{}
	//1 \r
	//2 \r\n
	//3 \n
	//一次读一个字符
	void RecvLine(string &line)
	{
		char c = 'A';
		while(c!='\n')
		{
			ssize_t s = recv(sock,&c,1,0);
			if(s>0)
			{
				if(c=='\r')
				{
					recv(sock,&c,1,MSG_PEEK);//窥探底层数据，并不拿走底层数据
					if(c=='\n')
						recv(sock,&c,1,0);
					else
						c = '\n';
				}
				line += c;
			}
			else
			{
				LOG(ERROR,"recv error!");
			}
		}
	}
	void RecvRequestLine(string& line)//读取请求行
	{
		RecvLine(line);
	}
	void RecvRequestHeader(string& header)//读取请求报头
	{
		string tmp;
		do
		{
			tmp="";
			RecvLine(tmp);
			if(tmp!="\n")
				header+=tmp;
		}while(tmp!="\n");
	}
	void RecvHttpRequest(HttpRequest*& rq)//设置http的请求行，请求报头以及空行
	{
		string rq_line;
		string rq_header;
		RecvRequestLine(rq_line);
		RecvRequestHeader(rq_header);
		rq->SetRequestLine(rq_line);
		rq->SetRequestHeader(rq_header);
	}
	void RecvHttpText(HttpRequest*& rq)//读取http的正文，并放在request_text中
	{
		int content_length = rq->GetContentLength();
		if(content_length > 0)
		{
			string text;
			char c;
			while(content_length>0)
			{
				recv(sock,&c,1,0);
				text+=c;
				content_length--;
			}
			rq->SetRequestText(text);
		}
		rq->SetRequestPath();
		rq->SetCgi();
	}
	~Connect()
	{}
private:
	int sock;
};
class Entry
{
public:
	static void* HandlerRequest(void*arg)
	{
		int* sock = (int*)arg;
		HttpRequest* rq = new HttpRequest();
		HttpResponse* rp = new HttpResponse();
		Connect* con = new Connect(*sock);
		//读取请求并拆分各个部分
		con->RecvHttpRequest(rq);
		//解析
		rq->DetachRequestLine();//分离请求行
		rq->DetachRequestHeader();//分离请求报头
		if(!rq->MethodIsOK())
		{
			LOG(WARNING,"method error!");
		}
		//url 域名/资源地址?AAA=BBB&CCC=DDD&...
		if(rq->MethodIsPost())//是POST方法
		{
			con->RecvHttpText(rq);//表明request请求全部读完
		}
		if(rq->MethodIsGet())
		{
			//1.分析请求路径是否携带参数,并将url进行分离
			rq->DetachUrl();
		}
		//2.分析请求资源是否合法
		if(rq->PathIsLegal())
		{

		}
		//制作响应
		//发送响应
		rq->show();
		delete rq;
		delete rp;
		delete con;
	}
};
