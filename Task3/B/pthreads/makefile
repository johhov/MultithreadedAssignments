# The compiler
CC = g++

# Flags for the compiler
CFLAGS = -std=c++11 -c -g -fpermissive -I.

LIBS = -pthread -lrt

# Name of the executable
EXECUTABLE = exe

# Source files
SOURCES = main.cpp SafeStack.cpp

# The objects
OBJECTS = $(SOURCES:.cpp=.o)

build: $(SOURCES) $(EXECUTABLE)

all: 
	build

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(LIBS) $< -o $@
 
clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
