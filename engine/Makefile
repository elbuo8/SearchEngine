# Makefile - R Arce
all: client

client: client.o ParsedFile.o Histogram.o
	c++ -pg -o client client.o ParsedFile.o Histogram.o

client.o: client.cpp ParsedFile.h Histogram.h
	c++ -pg -c client.cpp

ParsedFile.o: ParsedFile.cpp ParsedFile.h 
	c++ -pg -c ParsedFile.cpp

Histogram.o: Histogram.cpp Histogram.h
	c++ -pg -c Histogram.cpp

clean: 
	rm -rf *.o

pack:
	tar cvzf engine.tgz client.cpp ParsedFile.h ParsedFile.cpp Makefile
