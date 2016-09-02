struct Hero {
  int xpos;
  int ypos;
  int hp;
  int mp;
  char *name; 

  SDL_Surface *hero_back;
  SDL_Surface *hero_front; 
  SDL_Surface *hero_left; 
  SDL_Surface *hero_right; 

  SDL_Texture *hero_texture_front;
  SDL_Texture *hero_texture_back;
  SDL_Texture *hero_texture_left;
  SDL_Texture *hero_texture_right;
};

struct Hero *Hero_create(char *name, int ypos, int xpos, int hp, int mp, SDL_Renderer *renderer) {

  struct Hero *who = malloc(sizeof(struct Hero));

  who->name = strdup(name);
  who->xpos = xpos;
  who->ypos = ypos;
  who->hp = hp;
  who->mp = mp;
  
  who->hero_back = IMG_Load("hero_back.png");
  who->hero_front = IMG_Load("hero_front.png");
  who->hero_left = IMG_Load("hero_left.png");
  who->hero_right = IMG_Load("hero_right.png");

  who->hero_texture_front = SDL_CreateTextureFromSurface(renderer, who->hero_front);
  who->hero_texture_back = SDL_CreateTextureFromSurface(renderer, who->hero_back);
  who->hero_texture_left  = SDL_CreateTextureFromSurface(renderer, who->hero_left);
  who->hero_texture_right = SDL_CreateTextureFromSurface(renderer, who->hero_right);

  SDL_FreeSurface(who->hero_front);
  SDL_FreeSurface(who->hero_back);
  SDL_FreeSurface(who->hero_left);
  SDL_FreeSurface(who->hero_right);
  

  return who;
}

void Hero_destroy(struct Hero *who)
{
  assert(who != NULL);    
  free(who);
}
