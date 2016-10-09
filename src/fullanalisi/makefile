ogg:
	g++ -c analisigoccia.C average.C stdDev.C compat.C full.C
comp: ogg
	g++ analisigoccia.o average.o stdDev.o compat.o full.o -o full.x
ese: comp
	./full.x