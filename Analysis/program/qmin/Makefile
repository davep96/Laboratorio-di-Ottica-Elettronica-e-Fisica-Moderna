EXE = main
OBJ = qmin.o main.o sums.o
CFLAGS = -c -std=c++11
LIBS = lib.h

all: $(EXE)

main: $(OBJ) $(LIBS)
	c++ -o main $(OBJ)
main.o: main.cpp
	c++ $(CFLAGS) main.cpp
qmin.o: qmin.cpp
	c++ $(CFLAGS) qmin.cpp
sums.o: sums.cpp
	c++ $(CFLAGS) sums.cpp
clean:
	rm *.o
cleanall: clean
	rm $(EXE)