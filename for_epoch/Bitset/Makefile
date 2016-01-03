TARGET = bitset-test 
INC = -I./hpp
LIB =

CC = g++

CFLAGS = -g -Wall -std=c++11 -DDEBUG $(INC)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard ./hpp/*.hpp)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIB) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
