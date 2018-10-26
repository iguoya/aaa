CC = g++
CFLAGS = -g -Wall  `mysql_config --cflags`
CLIBS =  `mysql_config --libs` -lcrypto++ -ljsoncpp


all: server client
	$(CC) -o server MyServer.o Event.o $(CLIBS)
	./server

server:MyServer.o Event.o
MyServer.o:MyServer.cpp Event.h
	$(CC) -c $< $(CFLAGS)
Event.o:Event.cpp
	$(CC) -c $< $(CFLAGS)


# client:Login.o
# Login.o: Login.cpp
# 	$(CC) -c $< $(CFLAGS) 

clean:
	rm *.o server 
# app :
# 	g++ -c Event.cpp
# 	g++ -c MyServer.cpp
# 	g++ -o server MyServer.o Event.o
# 	./server &
# 	g++ -c Login.cpp `wx-config --cppflags`
# 	g++ -o client  Login.o `wx-config --libs`
# 	./client 
	# g++ -c Server.cpp `wx-config --cppflags`
	# g++ -o server  Server.o `wx-config --libs`
	# ./server

