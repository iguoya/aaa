CC = clang++
CFLAGS = `freetype-config --cflags`
LIBS = `freetype-config --libs`
all:
	$(CC) -c Unit_test.cpp $(CFLAGS)
	$(CC) -c Render.cpp $(CFLAGS)
	$(CC) -c Config.cpp $(CFLAGS)
	$(CC) -c Content.cpp $(CFLAGS)
	$(CC) Unit_test.o -o unit_test $(LIBS)
	./unit_test
