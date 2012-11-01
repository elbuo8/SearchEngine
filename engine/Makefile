#Makefile - R Arce
all: client

client: client.o ParsedFile.o Book.o Histogram.o
	c++ client.o ParsedFile.o Book.o Histogram.o -o client

client.o: client.cpp ParsedFile.h Book.h Histogram.h
	c++ -c -O3 client.cpp

ParsedFile.o: ParsedFile.cpp ParsedFile.h 
	c++ -c -O3 ParsedFile.cpp

Book.o: Book.cpp Book.h
	c++ -c -O3 Book.cpp

Histogram.o: Histogram.cpp Book.h Histogram.h
	c++ -c -O3 Histogram.cpp

clean: 
	rm -rf *.o

pack:
	tar cvzf engine.tgz client.cpp ParsedFile.h ParsedFile.cpp Makefile
