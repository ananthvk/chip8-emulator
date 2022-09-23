CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address
LIBRARY_PATH := -L./libraries/sdl2/lib -L./chip8-core -L./chip8-graphics
BIN_PATH := ./libraries/sdl2/bin
INCLUDE_PATH := -I./libraries/sdl2/include -I./chip8-core -I./chip8-graphics
LINKER_FLAG :=  -lchip8-core -lchip8-graphics -lSDL2 -lSDL2main

debug: all main

all:
	@$(MAKE) -C chip8-core
	cp ./chip8-core/chip8-core.dll .
	@$(MAKE) -C chip8-graphics
	cp ./chip8-graphics/chip8-graphics.dll .

main: main.o
	gcc *.o -o chip8 $(INCLUDE_PATH) $(LIBRARY_PATH) $(LINKER_FLAG)
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

	rm chip8-graphics/*.dll -f
	rm chip8-graphics/*.o -f
	rm chip8-graphics/*.exe -f