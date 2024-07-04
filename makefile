CC=gcc
CFLAGS= -Wall -g -Wextra
.PHONY: all clean
all: digitcompress
digitcompress: encodemain.o compress.o
	$(CC) $(CFLAGS) $^ -o $@
encodemain.o: encodemain.c compress.h
	$(CC) $(CFLAGS) -c $<
compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o digitcompress encodemain
