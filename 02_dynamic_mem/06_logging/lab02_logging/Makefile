CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = my_program

all: log_helper.o struct_helper.o main.o 
	$(CC) $(CFLAGS) -o $(BIN) log_helper.o struct_helper.o main.o


struct_helper.o: struct_helper.c 
	$(CC) $(CFLAGS) -c struct_helper.c 
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
log_helper.o: log_helper.c
	$(CC) $(CFLAGS) -c log_helper.c
	
chatty: log_helper.o struct_helper.o main.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) log_helper.o struct_helper.o main.o 
	@echo Finished
	
fsanitizer: log_helper.o struct_helper.o main.o 
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) log_helper.o struct_helper.o main.o

.PHONY: clean
clean:
	rm *.o $(BIN)
