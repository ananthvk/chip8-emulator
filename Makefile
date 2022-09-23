CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address
LIBRARY_PATH := -L./libraries/sdl2/lib -L./chip8-core
BIN_PATH := ./libraries/sdl2/bin
INCLUDE_PATH := -I./libraries/sdl2/include -I./chip8-core
LINKER_FLAG := -lSDL2main -lSDL2 -lchip8-core

debug: all main

all:
	@$(MAKE) -C chip8-core
	cp ./chip8-core/chip8-core.dll .

main: main.o
	gcc *.o -o chip8 -dynamic $(LIBRARY_PATH) $(LINKER_FLAG)
	cp $(BIN_PATH)/SDL2.dll .

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c -o $@ $< $(LINKER_FLAG)

clean:
	rm *.o -f
	rm *.exe -f
	rm *.dll -f
	rm chip8-core/*.dll -f
	rm chip8-core/*.o -f
	rm chip8-core/*.exe -f