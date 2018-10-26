#CC = arm-linux-gnueabihf-g++-4.7
CC = g++
INCLUDES = -I/usr/include/freetype2
CFLAGS = -g
LIBS = -lfreetype -lz -lm -lpthread 
#CHK_SOURCE = main.cpp tools.cpp
app:main.o tools.o
	$(CC) -o app main.o tools.o $(LIBS)
main.o:main.cpp tools.h
	$(CC) -c -g main.cpp $(INCLUDES)
tools.o:tools.cpp tools.h
	$(CC) -c -g tools.cpp $(INCLUDES)
info:
	gcc -o info fb_info.c -I/usr/include/freetype2 -lfreetype -lm
test:
	gcc -o test fb_test.c -I/usr/include/freetype2 -lfreetype -lm
clean:
	sudo rm *.o app
check-syntax:
	gcc -S main.cpp tools.cpp
