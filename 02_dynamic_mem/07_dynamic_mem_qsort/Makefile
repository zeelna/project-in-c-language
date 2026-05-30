CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = my_program

all: generator.o filename_helper.o
	$(CC) $(CFLAGS) -o $(BIN) generator.o filename_helper.o


filename_helper.o: filename_helper.c 
	$(CC) $(CFLAGS) -c filename_helper.c 
	
generator.o: generator.c
	$(CC) $(CFLAGS) -c generator.c
	
chatty: generator.o filename_helper.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) generator.o filename_helper.o 
	@echo Finished
	
fsan: generator.o filename_helper.o
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) generator.o filename_helper.o

.PHONY: clean
clean:
	rm *.o $(BIN) *.txt *.csv
