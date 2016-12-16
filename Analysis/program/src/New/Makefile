CFLAGS = -std=c++11
EXECUTABLES = quickplot
CLASSES = *cls.h

all: $(EXECUTABLES)

quickplot: quickplot.o $(CLASSES)
	c++ quickplot.o -o quickplot
	
quickplot.o: quickplot.cpp $(CLASSES)
	c++ -c $(CFLAGS) quickplot.cpp