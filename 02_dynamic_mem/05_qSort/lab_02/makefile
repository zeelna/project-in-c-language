CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
PKG_CONFIG = $(shell pkg-config --exists libcurl && pkg-config --cflags --libs libcurl)
LIBS = -lcurl
BIN = program

all: data_processor.o file_helper.o main.o 
	$(CC) $(CFLAGS) -o $(BIN) data_processor.o file_helper.o main.o -lcurl

data_processor.o : data_processor.c 
	$(CC) $(CFLAGS) -c data_processor.c  
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
file_helper.o: file_helper.c
	$(CC) $(CFLAGS) -c file_helper.c
	
	
fsan: file_helper.o data_processor.o main.o 
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) file_helper.o data_processor.o main.o -lcurl

.PHONY: clean
clean:
	rm *.o $(BIN)
