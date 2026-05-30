CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = my_program

all: linkedList.o 
	$(CC) $(CFLAGS) -o $(BIN) linkedList.o

linkedList.o: linkedList.c 
	$(CC) $(CFLAGS) -c linkedList.c 
	
chatty: linkedList.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) linkedList.o 
	@echo Finished
	
fsanitizer: linkedList.o
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) linkedList.o 

.PHONY: clean
clean:
	rm *.o $(BIN)
