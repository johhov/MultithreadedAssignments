CC=gcc
CFLAGS=-std=c++11 -pthread
DEPS=singleton.hpp
OBJ=main.o singleton.o

%.o %.cpp &(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

a: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o