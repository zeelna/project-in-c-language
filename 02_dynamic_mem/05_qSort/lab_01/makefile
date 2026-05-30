CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = program

all: employee_db.o array_helpers.o qsort_task.o 
	$(CC) $(CFLAGS) -o $(BIN) employee_db.o array_helpers.o qsort_task.o

employee_db.o : employee_db.c 
	$(CC) $(CFLAGS) -c employee_db.c  
	
qsort_task.o: qsort_task.c
	$(CC) $(CFLAGS) -c qsort_task.c
	
array_helpers.o: array_helpers.c
	$(CC) $(CFLAGS) -c array_helpers.c
	
	
fsan: employee_db.o array_helpers.o qsort_task.o 
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) employee_db.o array_helpers.o qsort_task.o

.PHONY: clean
clean:
	rm *.o $(BIN)
