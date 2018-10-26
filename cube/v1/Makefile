CC = g++
CFLAGS =  -g -Wall
all : app
	$(CC) -o  app main.o mf.o
app : main.o mf.o
main.o: main.cpp  mf.h
	$(CC) -c $(CFLAGS) main.cpp
mf.o: mf.cpp  mf.h
	$(CC) -c $(CFLAGS) mf.cpp 

clean:
	rm *.o app
