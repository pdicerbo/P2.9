CC=g++
CXXFLAGS=-O2 -Wall
SRCS=MyRNG.cpp
OBJS=$(SRCS:%.cpp=%.o)
EXE=../MyRNG.x

all: $(EXE)

../MyRNG.x: $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) -o  $@

%.o:%.cpp
	$(CC) -c $^

clean:
	rm -f *.o
