PRG = net-server-test
LIB_NAME = server
LIB = lib$(LIB_NAME).a
LIB_DIR = ./lib
INC = -I./hpp

CC = /home/build/BuildKit/BuildKit2_jtao/gcc/bin/g++
AR = ar 

CFLAGS = -g -Wall -std=c++11 -DDEBUG $(INC)
#CFLAGS = -Wall -std=c++11 -O3 $(INC)
LDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME) -lrt -lpthread

.PHONY: default all clean

default: $(PRG)
all: default

LIB_OBJS = $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
PRG_OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard ./hpp/*.hpp)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(PRG) $(LIB_OBJS) $(PRG_OBJS)

$(LIB): $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	#$(CC) -shared -fPIC -o $(LIB_DIR)/$@ $(LIB_OBJS) 
	${AR} -rv ${LIB_DIR}/$@ $?

$(PRG): $(LIB) $(PRG_OBJS)
	$(CC) $(PRG_OBJS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	-rm -f  $(LIB_OBJS) 
	-rm -fr $(LIB_DIR) 
	-rm -f  $(PRG_OBJS)
	-rm -f  $(PRG)
