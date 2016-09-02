#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 640
#define SPRITE_SIZE    32
#define SLEEP_TIME 90000000
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hero.h"
#include "move.h"

int xpos, ypos, direction;
bool start;

int retTime;

void sleep() {
  nanosleep((struct timespec[]){{0, SLEEP_TIME }}, NULL);
}

void event_handler(SDL_Event* event, bool* quit, SDL_Window* *window) {
  // Function that handles events
  switch (event->type) {  
  case SDL_FINGERDOWN: 
    // move right
    break;
  case SDL_KEYDOWN:  
    switch (event->key.keysym.sym) {
    case SDLK_s:
      start = true;
      break;
    case SDLK_ESCAPE:
      // Quit
      *quit = true;
      break;            
    case  SDLK_t:
      SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN_DESKTOP);
      break;
    case SDLK_UP:
      direction = UP;
      ypos = move_up(ypos);
      sleep();
      break;
    case SDLK_DOWN: 
      direction = DOWN;
      ypos = move_down(ypos);
      sleep();
      break;
    case SDLK_RIGHT:
      direction = RIGHT;
      xpos = move_right(xpos);  
      sleep();      
      break; 
    case SDLK_LEFT:
      direction = LEFT;
      xpos = move_left(xpos);
      sleep();
      break;       
    }
  }
}

int main()
{
  int x, y; 
  SDL_Window *window;
  SDL_Event event;
  
  SDL_Init(SDL_INIT_VIDEO);             
  start = false;
  window = SDL_CreateWindow(
			    "Grassland",                  // window title
			    SDL_WINDOWPOS_CENTERED,           // initial x position
			    SDL_WINDOWPOS_CENTERED,           // initial y position
			    SCREEN_WIDTH,                      // width, in pixels
			    SCREEN_HEIGHT,                     // height, in pixels,
			    SDL_WINDOW_OPENGL                  // flags - see below
			    );
  // SDL_WINDOW_ALLOW_HIGHDPI 
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  struct Hero *h = Hero_create("Tester", 1, 1, 1, 1, renderer);
  // Surfaces
  SDL_Surface *ground = SDL_LoadBMP("grass2.bmp");
  // Textures
  SDL_Texture *ground_texture =  SDL_CreateTextureFromSurface(renderer,
							      ground);
  SDL_FreeSurface(ground);
  SDL_Texture *dry_grass_texture =  SDL_CreateTextureFromSurface(renderer,
							 dry_grass);
  SDL_FreeSurface(dry_grass);
  bool quit = false;

  
  // Main Loop
  while (!quit)
    {
      while(SDL_PollEvent(&event))
	{
	  switch (event.type) {
	  case SDL_QUIT:
	    quit = true;
	    break;
	  case SDL_KEYDOWN:
	    start = true;
	    break; 
	  }  
	}
    
	for(x=0; x<SCREEN_WIDTH; x+=32) {
	  for(y=0; y<SCREEN_HEIGHT; y+=32){ 
                
	    SDL_Rect src = { 0, 0, 16, 16 }; 
	    SDL_Rect dst = { x, y, SPRITE_SIZE, SPRITE_SIZE };        
	    SDL_Rect src2 = { 0 , 0, 32, 32};
	    SDL_Rect dst3 = { x, y, SPRITE_SIZE, SPRITE_SIZE};
          	  
	    if(x == xpos && y == ypos) {
	      if (direction == UP) {     
		SDL_RenderCopy(renderer,h->hero_texture_back, &src2, &dst3);
	      }
                    
	      if (direction == DOWN) {
		SDL_RenderCopy(renderer, h->hero_texture_front, &src2, &dst3);
	      }
                    
	      if (direction == RIGHT) {
		SDL_RenderCopy(renderer, h->hero_texture_right, &src2, &dst3);
	      }
                    
	      if (direction == LEFT) {
		SDL_RenderCopy(renderer, h->hero_texture_left, &src2, &dst3);
	      }
                    
	    } else {
		SDL_RenderCopy(renderer, ground_texture, &src, &dst);
	    }
	  }
	}
      SDL_RenderSetLogicalSize(renderer, 480, 640);
      SDL_RenderPresent(renderer);
      event_handler(&event, &quit, &window);
    }
        
  // Clean up
  SDL_DestroyTexture(h->hero_texture_front);
  SDL_DestroyTexture(h->hero_texture_back);
  SDL_DestroyTexture(h->hero_texture_right);
  SDL_DestroyTexture(h->hero_texture_left);
  SDL_DestroyTexture(ground_texture);
 
  SDL_DestroyRenderer(renderer);  
  SDL_DestroyWindow(window);

  Hero_destroy(h);
    
  IMG_Quit();
  SDL_Quit();
  return 0;    
}
