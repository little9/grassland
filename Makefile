CC=clang

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)


CFLAGS=-Wall -g $(SDL_CFLAGS) $(SDL_LDFLAGS) $(pkg-config --cflags SDL2_image) $(pkg-config --libs SDL2_image) -lSDL2_image

clean:
	rm -f main
