#ifndef ASSETS_H
#define ASSETS_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <rftg.h>

extern SDL_Texture* image_cache[AVAILABLE_DESIGN];
extern SDL_Texture* card_back;
extern SDL_Texture* goal_cache[100];
extern SDL_Texture* icon_cache[100];
extern SDL_Texture* action_cache[100];

int load_assets(SDL_Renderer* renderer);
void free_assets(void);

#endif
