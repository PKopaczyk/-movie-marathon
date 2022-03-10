CFLAGS = -Wall -Wextra -std=c11 -O2
CC = gcc

all: main
	
main: main.o Tree.o List.o
	@$(CC) $(CFLAGS) -o main main.o List.o Tree.o

List.o: List.c List.h
	@$(CC) $(CFLAGS) -c List.c

Tree.o: Tree.c Tree.h List.h List.c
	@$(CC) $(CFLAGS) -c Tree.c

main.o: main.c Tree.h List.h Tree.c List.c
	@$(CC) $(CFLAGS) -c main.c

clean:
	@rm List.o
	@rm Tree.o
	@rm main.o
	@rm main