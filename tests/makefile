all: run libutil threads.o parser.o 

run: libutil
	@gcc -g -o ../bin/run run.c -pthread -L../lib -lutil -Wall -lrt 

libutil: threads.o parser.o
	@ar crs ../lib/libutil.a ../bin/parser.o ../bin/threads.o 

threads.o: ../src/threads.c parser.o
	@gcc -c ../src/threads.c -o ../bin/threads.o 

parser.o: ../src/parser.c
	@gcc -c ../src/parser.c -o ../bin/parser.o

clean:
	@rm -rf ../bin/*.o
	@rm -rf ../bin/run 
	@rm -rf ../lib/libutil.a


