CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address
debug: build
build: vm.c main.c cpu.c opcodes.c opcode_helpers.c opcodes_8xxx.c
	$(CC) $(CFLAGS) vm.c -c -o vm.o
	$(CC) $(CFLAGS) main.c -c -o main.o
	$(CC) $(CFLAGS) opcodes.c -c -o opcodes.o
	$(CC) $(CFLAGS) cpu.c -c -o cpu.o
	$(CC) $(CFLAGS) opcode_helpers.c -c -o opcode_helpers.o
	$(CC) $(CFLAGS) opcodes_8xxx.c -c -o opcodes_8xxx.o
	$(CC) $(CFLAGS) opcodes_8xxx.o opcodes.o opcode_helpers.o main.o cpu.o vm.o -o chip8



run: build
	chip8

clean:
	rm *.exe
