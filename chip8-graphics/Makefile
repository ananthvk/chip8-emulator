CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -O0 -ggdb3# -fsanitize=address
LIBRARY_PATH := -L../libraries/sdl2/lib
INCLUDE_PATH := -I../libraries/sdl2/include
LINKER_FLAG := -lSDL2main -lSDL2

chip8-graphics: graphics.o
	gcc *.o $(INCLUDE_PATH) $(LIBRARY_PATH) -fPIC -shared -o chip8-graphics.dll $(LINKER_FLAG)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c -o $@ $< $(LINKER_FLAG)

clean:
	rm *.o -f
	rm *.exe -f
	rm *.dll -f

