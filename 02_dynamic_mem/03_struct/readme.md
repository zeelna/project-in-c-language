// Step #1: Compile code into binary
gcc -o prog -fsanitize=address 03_struct.c

// Step #2: Run the binary to read file. Usage: ./prog data_file
./prog 03_data_short.txt
