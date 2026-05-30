// #1. Compile code to executable binary with the following command:
gcc -Wall -Wextra -Wconversion -o ex01 ex01.c

// #2. Run 'find' with newly created binary "ex01" with the following command:
find ./lab_cat -type f -printf '%f\n' | ./ex01

