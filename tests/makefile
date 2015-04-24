all: run-processes libutil-processes  run-threads libutil-threads processes.o matrix.o threads.o parser.o 

run-processes: libutil-processes
	@gcc -g -o ../bin/run-processes run-processes.c -L../lib -lutilp -Wall -lrt 

libutil-processes: processes.o matrix.o parser.o
	@ar crs ../lib/libutilp.a ../bin/processes.o ../bin/matrix.o ../bin/parser.o

run-threads: libutil-threads
	@gcc -g -o ../bin/run-threads run-threads.c -pthread -L../lib -lutilt -Wall -lrt 

libutil-threads: threads.o parser.o
	@ar crs ../lib/libutilt.a ../bin/threads.o ../bin/parser.o

processes.o: ../src/processes.c matrix.o
	@gcc -c ../src/processes.c -o ../bin/processes.o 

matrix.o: ../src/matrix.c parser.o
	@gcc -c ../src/matrix.c -o ../bin/matrix.o 

threads.o: ../src/threads.c parser.o
	@gcc -c ../src/threads.c -o ../bin/threads.o 

parser.o: ../src/parser.c
	@gcc -c ../src/parser.c -o ../bin/parser.o

clean:
	@rm -rf ../bin/*.o
	@rm -rf ../bin/run-threads
	@rm -rf ../lib/libutil-threads.a
	@rm -rf ../bin/run-processes
	@rm -rf ../lib/libutil-processes.a


