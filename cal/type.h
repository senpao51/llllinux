#pragma once 

typedef struct request
{
	int x;
	int y;
	char op;
}request_t;

typedef struct response
{
	int status;
	int result;
}response_t;
