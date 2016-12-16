ogg:
	g++ -c analisigoccia.C average.C stdDev.C compat.C
comp: ogg
	g++ analisigoccia.o average.o stdDev.o compat.o -o analisigoccia.x
ese: comp
	./analisigoccia.x