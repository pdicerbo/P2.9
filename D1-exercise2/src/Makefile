CC=g++
CXXFLAGS=-O2 -Wall -std=c++11
SRCS=MyRNG.cpp main.cpp 
OBJS=$(SRCS:%.cpp=%.o)
EXE=../main.x

all: $(EXE)

../main.x: $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) -o  $@

%.o:%.cpp
	$(CC) $(CXXFLAGS) -c $^

debug: CXXFLAGS += -D__DEBUG
debug: all

clean:
	rm -f *.o
