CC = gcc
CFLAGS = -Wall -std=c99

all: performance_test

string_matching_naive.o: string_matching_naive.c string_matching.h 
	$(CC) $(CFLAGS) -c string_matching_naive.c

string_matching_kmp.o: string_matching_kmp.c string_matching.h
	$(CC) $(CFLAGS) -c string_matching_kmp.c
	
performance_test.o: performance_test.c string_matching.h
	$(CC) $(CFLAGS) -c performance_test.c

	
tesi: string_matching_naive.o string_matching_kmp.o performance_test.o
	$(CC) $(CFLAGS) -o performance_test string_matching_naive.o string_matching_kmp.o performance_test.o

clean:
	rm *.o performance_test
