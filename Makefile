# -*- MakeFile -*-
#target: dependencies
#   action

#CC = gcc
#CFLAGS = -O0 -g -Wall -Werror

all: main

#main: main.c
#	gcc -g convolve.c main.c convolve.h -o main

EXECUTABLE=main

main: list.o main.c
	gcc -g list.o read_data.h read_data.c convolve.c convolve.h diff.c diff.h detect_cusum.h detect_cusum.c  main.c  -o $(EXECUTABLE)

read_data.o:read_data.h read_data.c
	gcc -g -c read_data.h read_data.c

list.o: list.h list.c
	gcc -g -c list.h list.c

test: test.c
	gcc -g convolve.c read_data.c read_data.h diff.c test.c diff.h convolve.h -o test
clean:
	rm  main test

run:
	./main&&test
leaks:
	valgrind --leak-check=yes ./$(EXECUTABLE)
profile:
	valgrind --tool=massif --time-unit=B ./$(EXECUTABLE)
#heap profiler
# ms_print  massif.out.<PID>
#http://valgrind.org/docs/manual/ms-manual.html
