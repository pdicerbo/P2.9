CC=g++
CXXFLAGS=-O2 -Wall
SRCS=MyRNG.cpp
OBJS=$(SRCS:%.cpp=%.o)
EXE=../MyRNG.x

all: $(EXE)

../MyRNG.x: $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) -o  $@

%.o:%.cpp
	$(CC) $(CXXFLAGS) -c $^

debug: CXXFLAGS += -D__DEBUG
debug: all

clean:
	rm -f *.o
