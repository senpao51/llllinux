#pragma once 
#include "Log.h"
#include "Util.h"
#include "ThreadPool.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
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
	HttpRequest():blank("\n"),path(DEFAULT_ROOT),cgi(false),fd(-1)
	{}
	~HttpRequest()
	{
		if(fd>=0)
			close(fd);
	}
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
		bool flag = true;
		struct stat st;
		if(stat(path.c_str(),&st)==0)
		{
			//请求资源存在
			if(S_ISDIR(st.st_mode))//判断是路径否一个是目录
			{
				if(path[path.size()-1]!='/')
					path+='/';
				path += DEFAULT_PAGE;
				cout<<"***************path"<<path<<endl;
			}
			else if((st.st_mode&S_IXUSR)||(st.st_mode&S_IXGRP)||(st.st_mode&S_IXOTH))// 判断是否具有可执行权限 cgi程序必须具有可执行权限
				cgi = true;
			else
			{
				//路径合法
			}
			file_size = st.st_size;
			auto pos = path.rfind('.');
			if(pos==string::npos)
			{
				suffix = ".html";
			}
			else
			{
				suffix = path.substr(pos);	
			}
		}
		else
		{
			//请求资源不存在
			//404
			flag = false;
		}
		return flag;
	}
	bool IsCgi()
	{
		return cgi;
	}
	bool OpenResources()//打开资源，只读方式
	{
		bool flag = true;
		fd = open(path.c_str(),O_RDONLY);
		if(fd<0)
			flag = false;
		return true;
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
	int GetFileSize()
	{
		return file_size;
	}
	int GetFd()
	{
		return fd;
	}
	string& GetSuffix()
	{
		return suffix;
	}
	string& GetParameter()
	{
		return parameter;
	}
	string& GetRequestText()
	{
		return request_text;
	}
	string& GetPath()
	{
		return path;
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
		if(url=="/")
			url+=DEFAULT_PAGE;
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
	int file_size;
	int fd;
	string suffix;//文件名后缀
};
class HttpResponse
{
public:
	HttpResponse():blank("\n")
	{}
	~HttpResponse()
	{}	
public:
	void SetResponseLine(string& line)
	{
		response_line = line;
	}
	void SetResponseHeader(string& line)
	{
		if(response_header.empty())
		{
			response_header = line;
		}
		else
		{
			response_header += line;
		}
	}
	void SetResponseText(string& text)
	{
		response_text = text;
	}
public:
	string& GetResponseLine()
	{
		return response_line;
	}
	string& GetResponseHeader()
	{
		return response_header;
	}
	string& GetBlank()
	{
		return blank;
	}
	string& GetResponseText()
	{
		return response_text;
	}
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
	~Connect()
	{
		if(sock>=0)
			close(sock);
	}
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
	void SendResponse(HttpRequest* rq,HttpResponse* rp)//发送响应
	{
		string line = rp->GetResponseLine();
		line += rp->GetResponseHeader();
		line += rp->GetBlank();
		send(sock,line.c_str(),line.size(),0);//发送响应行，响应报头，空行
		if(rq->IsCgi())
		{
			string text = rp->GetResponseText();
			send(sock,text.c_str(),text.size(),0);
		}
		else
		{
			sendfile(sock,rq->GetFd(),nullptr,rq->GetFileSize());//发送响应正文
		}
	}
private:
	int sock;
};
class Entry
{
public:
	static void MakeResponse(HttpRequest* rq,HttpResponse* rp,int code)
	{
		string line = Util::GetResponseLine(code);
		rp->SetResponseLine(line);//设置响应行
		line = "Content-Type: ";
		line+=Util::SuffixToType(rq->GetSuffix());
		line+="\r\n";
		rp->SetResponseHeader(line);
		line = "Content-Length: ";
		if(rq->IsCgi())
		{
			//cgi
			string text = rp->GetResponseText();
			line += Util::IntToString(text.size());
			line += "\r\n";
			line += "\r\n";//空行
			rp->SetResponseHeader(line);//设置响应报头，空行		
		}
		else
		{
			//nocgi
			line += Util::IntToString(rq->GetFileSize());
			line += "\r\n";//空行
			line += "\r\n";//空行
			rp->SetResponseHeader(line);//设置响应报头，空行		
			if(!rq->OpenResources())//打开资源
			{
				LOG(ERROR,"open resources failed!");
			}
			else
			{
				//打开文件资源成功
				LOG(NORMAL,"open resources successfully!");
			}
		}
	}
	static int ProcessByCgi(Connect* con,HttpRequest* rq,HttpResponse* rp)
	{
		//CGI
		//读写站在子进程角度
		//子进程用来处理CGI模块数据，父进程通过管道读取处理好的数据
		int read_pipe[2];
		int write_pipe[2];
		pipe(read_pipe);
		pipe(write_pipe);
		string content_length;
		string args;//参数
		if(rq->MethodIsGet())
		{
			args = rq->GetParameter();
		}
		if(rq->MethodIsPost())
		{
			args = rq->GetRequestText();
		}
		pid_t id = fork();
		if(id==0)
		{
			//child
			//通过read_pipe来读，关闭写端，通过write_pipe来写，关闭读端
			close(read_pipe[1]);
			close(write_pipe[0]);
			string path = rq->GetPath();//rq->path 要让子进程执行的程序  parameter(GET)  request_text(POST)
			//约定0号文件描述符读取，往1文件描述符打印
			//0->read_pipe[0]   1->write_pipe[1]
			dup2(read_pipe[0],0);
			dup2(write_pipe[1],1);
			content_length = "Content-Length: ";
			content_length += Util::IntToString(args.size());
			putenv((char*)content_length.c_str());//将读取数据的长度导入环境变量里
			//程序替换
			execl(path.c_str(),path.c_str(),nullptr);//执行CGI程序，默认显示到显示器，要想办法输出到文件中，增加约定，利用重定向技术，完成文件描述符的约定
			exit(1);//execl程序如果出错，直接退出
		}
		else if(id>0)
		{
			//father
			//通过read_pipe来写，关闭读端，通过write_pipe来读，关闭写端
			close(read_pipe[0]);
			close(write_pipe[1]);
			for(int i=0;i<args.size();i++)
			{
				write(read_pipe[1],&args[i],1);//向read_pipe中写入path所对应的数据
			}
			char c;
			string msg = "";//http响应数据
			while(read(write_pipe[0],&c,1)>0)//向write_pipe中读取子进程处理好的数据
			{
				msg+=c;
			}
			//将msg设置为response_text中
			rp->SetResponseText(msg);
			pid_t ret = waitpid(id,nullptr,0);
			if(ret<0)
			{
				LOG(WARNING,"waitpid child error!");
				return 404;
			}
		}
		else
		{
			//error
			LOG(ERROR,"fork error!");
			return 404;
		}
		return 200;//cgi成功
	}
	static void* HandlerRequest(void*arg)
	{
		int code = 200;
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
			code = 404;
			LOG(WARNING,"method error!");
			goto end;
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
		if(!rq->PathIsLegal())
		{
			code = 404;
			LOG(WARNING,"path is not legal!");
			goto end;
		}
		//请求全部处理完，包括请求行分离，请求报头分离，url解析，方法确定，cgi设置，
		if(rq->IsCgi())
		{
			//cgi的处理方法   带参数，解析参数
			LOG(NORMAL,"exec by cgi!");
			code = ProcessByCgi(con,rq,rp);
		}
		else
		{
			//非cgi的处理方法  不带参数，请求资源而已
			LOG(NORMAL,"exec no cgi!");
		}
end:
		MakeResponse(rq,rp,code);//制作响应
		con->SendResponse(rq,rp);//发送响应
		//rq->show();
		delete rq;
		delete rp;
		delete con;
	}
};
