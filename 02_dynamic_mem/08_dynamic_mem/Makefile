CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = my_program

all: main.o write_output.o
	$(CC) $(CFLAGS) -o $(BIN) main.o write_output.o


write_output.o: write_output.c 
	$(CC) $(CFLAGS) -c write_output.c 
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
chatty: main.o write_output.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) main.o write_output.o 
	@echo Finished
	
fsan: main.o write_output.o
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) main.o write_output.o

.PHONY: clean
clean:
	rm *.o $(BIN)
