#pragma once 
#include "Log.h"
#include "Util.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>
#include <strings.h>
#include <unordered_map>
using namespace std;
class HttpRequest
{
public:
	HttpRequest():blank("\n")
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
	void SetRequestPath(string& _path)
	{
		path = _path;
	}
public:
	int GetContentLength()
	{
		auto it = header_map.find("Content-Length");
		if(it==header_map.end())
		{
			LOG(WARNING,"request_text is not exist!");
			return -1;
		}
		return Util::StringToInt(it->second);
	}
public:
	void DetachUrl()
	{
		//url = 资源路径path+ ? +参数parameter(有可能不存在)
		auto p = url.find('?');
		if(p!=string::npos)
		{
			path = url;
		}
		else
		{
			path = url.substr(0,p);
			parameter = url.substr(p+1);
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
	cout<<"request = "<<request_text;
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
		rq->DetachRequestLine();
		rq->DetachRequestHeader();
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
		if(!rq->MethodIsOK())
		{
			LOG(WARNING,"method error!");
		}
		//url 域名/资源地址?AAA=BBB&CCC=DDD&...
		if(!rq->MethodIsGet())//是POST方法
		{
			//Post方法
			con->RecvHttpText(rq);//表明request请求全部读完
		}
		//GET方法
		//1.分析请求路径是否携带参数,
		if(rq->MethodIsGet())
		{
			rq->DetachUrl();
		}
		//2.分析请求资源是否合法
		//制作响应
		//发送响应
		rq->show();
		delete rq;
		delete rp;
		delete con;
	}
};
