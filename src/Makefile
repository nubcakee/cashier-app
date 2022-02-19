TARGET = CashApp

VPATH = ../headers

OBJECTS = stock.o io.o database.o

LIBS = -lsqlite3

$(TARGET): main.cpp $(OBJECTS)
		g++ main.cpp $(OBJECTS) $(LIBS) -o $@

clean:
	rm *.o
