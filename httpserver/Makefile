.PHONY:all
all:httpserver testcgi
httpserver:main.cpp
	g++ -o $@ $^ -std=c++11 -lpthread
testcgi:testcgi.cpp
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f httpserver testcgi

.PHONY:output
output:
	mv testcgi ./page/cgi
