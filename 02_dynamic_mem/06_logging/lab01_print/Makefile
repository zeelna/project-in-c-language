CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
BIN = my_program

all: struct_helper.o main.o
	$(CC) $(CFLAGS) -o $(BIN) struct_helper.o main.o


struct_helper.o: struct_helper.c
	$(CC) $(CFLAGS) -c struct_helper.c
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
chatty: struct_helper.o main.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) struct_helper.o main.o
	@echo Finished

.PHONY: clean
clean:
	rm *.o $(BIN)
