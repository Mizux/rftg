#include "assets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SDL_Texture* image_cache[AVAILABLE_DESIGN];
SDL_Texture* card_back = NULL;
SDL_Texture* goal_cache[100];
SDL_Texture* icon_cache[100];
SDL_Texture* action_cache[100];

static SDL_Texture* load_texture_from_mem(SDL_Renderer* renderer,
                                          const void* data, size_t size) {
  SDL_IOStream* io = SDL_IOFromConstMem(data, size);
  if (!io) return NULL;
  SDL_Surface* surface = IMG_Load_IO(io, true);
  if (!surface) return NULL;
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return texture;
}

int load_assets(SDL_Renderer* renderer) {
  FILE* fp = fopen("images.data", "rb");
  if (!fp) {
    fp = fopen(RFTGDIR "/images.data", "rb");
  }
  if (!fp) {
    fprintf(stderr, "Error: Could not find images.data\n");
    return -1;
  }

  char header[4];
  if (fread(header, 1, 4, fp) != 4 || strncmp(header, "RFTG", 4) != 0) {
    fprintf(stderr, "Error: Image bundle missing header!\n");
    fclose(fp);
    return -1;
  }

  while (1) {
    unsigned char type;
    if (fread(&type, 1, 1, fp) != 1 || type == 0) break;

    char id_buf[5] = {0};
    int id_len = (type == 1) ? 4 : 3;
    if (fread(id_buf, 1, id_len, fp) != id_len) break;
    int id = atoi(id_buf);

    char size_buf[9] = {0};
    if (fread(size_buf, 1, 8, fp) != 8) break;
    size_t size = atoll(size_buf);

    void* data = malloc(size);
    if (fread(data, 1, size, fp) != size) {
      free(data);
      break;
    }

    SDL_Texture* texture = load_texture_from_mem(renderer, data, size);
    free(data);

    if (!texture) continue;

    SDL_Texture** ptr = NULL;
    switch (type) {
      case 1:
        if (id >= 0 && id < AVAILABLE_DESIGN) ptr = &image_cache[id];
        break;
      case 2:
        ptr = &card_back;
        break;
      case 3:
        if (id >= 0 && id < 100) ptr = &goal_cache[id];
        break;
      case 4:
        if (id >= 0 && id < 100) ptr = &icon_cache[id];
        break;
      case 5:
        if (id >= 0 && id < 100) ptr = &action_cache[id];
        break;
    }

    if (ptr) {
      if (*ptr) SDL_DestroyTexture(*ptr);
      *ptr = texture;
    } else {
      SDL_DestroyTexture(texture);
    }
  }

  fclose(fp);
  return 0;
}

void free_assets(void) {
  for (int i = 0; i < AVAILABLE_DESIGN; i++) {
    if (image_cache[i]) SDL_DestroyTexture(image_cache[i]);
    image_cache[i] = NULL;
  }
  if (card_back) SDL_DestroyTexture(card_back);
  card_back = NULL;
  for (int i = 0; i < 100; i++) {
    if (goal_cache[i]) SDL_DestroyTexture(goal_cache[i]);
    goal_cache[i] = NULL;
    if (icon_cache[i]) SDL_DestroyTexture(icon_cache[i]);
    icon_cache[i] = NULL;
    if (action_cache[i]) SDL_DestroyTexture(action_cache[i]);
    action_cache[i] = NULL;
  }
}
