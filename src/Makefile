VPATH = ../headers

OBJECTS = stock.o io.o database.o

LIBS = -lsqlite3

main: main.cpp $(OBJECTS)
		g++ main.cpp $(OBJECTS) $(LIBS) -o main

clean:
	rm *.o
