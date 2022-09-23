CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address

chip8-core: opcode_helpers.o opcodes_8xxx.o opcodes.o vm.o cpu.o
	gcc *.o -o -fPIC -shared -o chip8-core.dll

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o
	rm *.exe