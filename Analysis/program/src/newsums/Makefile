EXECUTABLES = sums
CFLAGS = -c -std=c++11


all: $(EXECUTABLES)

sums: sums.o
	c++ sums.o -o sums
sums.o: sums.cpp
	c++ $(CFLAGS) sums.cpp
