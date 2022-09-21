CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3 -Wno-return-type -Wno-unused-parameter
debug: build
build: vm.c main.c cpu.c opcodes.c
	$(CC) $(CFLAGS) vm.c main.c cpu.c opcodes.c -o chip8 

run: build
	chip8

clean:
	rm *.exe
