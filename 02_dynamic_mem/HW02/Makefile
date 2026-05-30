CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wconversion -g
SANITIZER = -fsanitize=address
BIN = my_program

all: main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o
	$(CC) $(CFLAGS) -o $(BIN) main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o

search.o: search.c
	$(CC) $(CFLAGS) -c search.c 

print_results.o: print_results.c
	$(CC) $(CFLAGS) -c print_results.c 

read_product.o: read_product.c 
	$(CC) $(CFLAGS) -c read_product.c 
	
read_quote.o: read_quote.c 
	$(CC) $(CFLAGS) -c read_quote.c 	

ask_input.o: ask_input.c 
	$(CC) $(CFLAGS) -c ask_input.c 	
	
log_helper.o: log_helper.c 
	$(CC) $(CFLAGS) -c log_helper.c 
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
chatty: main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o
	@echo Starting build
	$(CC) $(CFLAGS) -o $(BIN) main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o
	@echo Finished
	
fsan: main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o
	$(CC) $(CFLAGS) $(SANITIZER) -o $(BIN) main.o search.o read_product.o read_quote.o print_results.o ask_input.o log_helper.o

.PHONY: clean
clean:
	rm *.o $(BIN)
	
clean-logs:
	rm *.o $(BIN) *.log *.txt

	
