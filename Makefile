CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address
LIBRARY_PATH := -L./libraries/sdl2/lib
INCLUDE_PATH := -I./libraries/sdl2/include
LINKER_FLAG := -lSDL2main -lSDL2

chip8.exe: main.o opcode_helpers.o opcodes_8xxx.o opcodes.o vm.o cpu.o
	gcc *.o -o chip8.exe $(LIBRARY_PATH) $(LINKER_FLAG)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c -o $@ $< $(LINKER_FLAG)

clean:
	rm *.o
	rm *.exe