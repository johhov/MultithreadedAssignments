# The compiler
CC = g++

# Flags for the compiler
CFLAGS = -std=c++11 -c -g -I. 

LIBS = -pthread

# Name of the executable
EXECUTABLE = exe

# Source files
SOURCES = main.cpp Callbacks.cpp

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
	clear
