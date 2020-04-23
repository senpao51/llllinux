.PHONY:all
all:client server
client:client.cpp
	g++ -o $@ $^ -std=c++11 
server:server.cpp
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f client server
