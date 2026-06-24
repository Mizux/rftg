#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <comm.h>
#include <rftg.h>

#include "assets.h"

static int server_fd = -1;
static game real_game;
static int player_us = -1;
static int client_state = CS_DISCONN;

void send_msg(int fd, char* msg) {
  int size, sent = 0, x;
  char* ptr = msg + 4;
  size = get_integer(&ptr);
  while (sent < size) {
    x = send(fd, msg + sent, size - sent, 0);
    if (x < 0) {
      if (errno == EPIPE || errno == ECONNRESET) return;
      perror("send");
      return;
    }
    sent += x;
  }
}

static void handle_status_meta(char* ptr) {
  real_game.num_players = get_integer(&ptr);
  real_game.expanded = get_integer(&ptr);
  real_game.advanced = get_integer(&ptr);
  real_game.goal_disabled = get_integer(&ptr);
  real_game.takeover_disabled = get_integer(&ptr);
  init_game(&real_game);
  for (int i = 0; i < MAX_GOAL; i++)
    real_game.goal_active[i] = get_integer(&ptr);
  for (int i = 0; i < real_game.num_players; i++) {
    char name[1024];
    get_string(name, &ptr);
    if (real_game.p[i].name) free(real_game.p[i].name);
    real_game.p[i].name = strdup(name);
  }
}

static void handle_status_player(char* ptr) {
  int x = get_integer(&ptr);
  player* p_ptr = &real_game.p[x];
  p_ptr->action[0] = get_integer(&ptr);
  p_ptr->action[1] = get_integer(&ptr);
  p_ptr->prestige_action_used = get_integer(&ptr);
  for (int i = 0; i < MAX_GOAL; i++) {
    p_ptr->goal_claimed[i] = get_integer(&ptr);
    p_ptr->goal_progress[i] = get_integer(&ptr);
  }
  p_ptr->prestige = get_integer(&ptr);
  p_ptr->vp = get_integer(&ptr);
  p_ptr->phase_bonus_used = get_integer(&ptr);
  p_ptr->bonus_military = get_integer(&ptr);
  p_ptr->bonus_reduce = get_integer(&ptr);
}

static void handle_status_card(char* ptr) {
  int x = get_integer(&ptr);
  card* c_ptr = &real_game.deck[x];
  int owner = get_integer(&ptr);
  int start_owner = get_integer(&ptr);
  int where = get_integer(&ptr);
  int start_where = get_integer(&ptr);
  move_card(&real_game, x, owner, where);
  move_start(&real_game, x, start_owner, start_where);
  c_ptr->misc = get_integer(&ptr);
  c_ptr->order = get_integer(&ptr);
  c_ptr->num_goods = get_integer(&ptr);
  c_ptr->covering = get_integer(&ptr);
}

static void handle_status_misc(char* ptr) {
  real_game.round = get_integer(&ptr);
  real_game.vp_pool = get_integer(&ptr);
  for (int i = 0; i < MAX_ACTION; i++)
    real_game.action_selected[i] = get_integer(&ptr);
  real_game.cur_action = get_integer(&ptr);
}

void display_error(char* msg) { fprintf(stderr, "%s", msg); }

void message_add(game* g, char* msg) {}
void message_add_formatted(game* g, char* msg, char* tag) {}

int game_rand(game* g) { return simple_rand(&g->random_seed); }

static void message_read(char* data) {
  char* ptr = data;
  int type = get_integer(&ptr);
  int size = get_integer(&ptr);
  switch (type) {
    case MSG_STATUS_META:
      printf("Received MSG_STATUS_META\n");
      handle_status_meta(ptr);
      break;
    case MSG_STATUS_PLAYER:
      handle_status_player(ptr);
      break;
    case MSG_STATUS_CARD:
      handle_status_card(ptr);
      break;
    case MSG_STATUS_MISC:
      handle_status_misc(ptr);
      break;
    case MSG_SEAT:
      player_us = get_integer(&ptr);
      printf("Joined as player %d\n", player_us);
      break;
    case MSG_HELLO:
      client_state = CS_LOBBY;
      printf("Logged in successfully\n");
      break;
    case MSG_CHAT:
    case MSG_GAMECHAT: {
      char who[1024], msg[1024];
      get_string(who, &ptr);
      get_string(msg, &ptr);
      printf("Chat [%s]: %s\n", who, msg);
    } break;
    case MSG_GAMEOVER:
      printf("Game Over\n");
      break;
  }
}

static void network_update(void) {
  static char buf[8192];
  static int buf_full = 0;
  if (server_fd < 0) return;

  int to_read;
  if (buf_full < 8) {
    to_read = 8 - buf_full;
  } else {
    char* ptr = buf + 4;
    int size = get_integer(&ptr);
    if (size > sizeof(buf)) {
      fprintf(stderr, "Message too large: %d\n", size);
      close(server_fd);
      server_fd = -1;
      return;
    }
    to_read = size - buf_full;
  }

  if (to_read <= 0) return;

  int x = recv(server_fd, buf + buf_full, to_read, 0);
  if (x > 0) {
    buf_full += x;
    if (buf_full >= 8) {
      char* ptr = buf + 4;
      int size = get_integer(&ptr);
      if (buf_full == size) {
        message_read(buf);
        buf_full = 0;
      }
    }
  } else if (x == 0 || (x < 0 && errno != EAGAIN)) {
    if (x < 0) perror("recv");
    close(server_fd);
    server_fd = -1;
    client_state = CS_DISCONN;
    printf("Disconnected from server\n");
  }
}

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
  SDL_Window* window = SDL_CreateWindow("RFTG SDL3 Client", 1024, 768, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  if (load_assets(renderer) < 0) return 1;
  read_cards(NULL);

  struct sockaddr_in serv_addr = {0};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5333);
  struct hostent* server = gethostbyname("localhost");
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==
      0) {
    fcntl(server_fd, F_SETFL, O_NONBLOCK);
    send_msgf(server_fd, MSG_LOGIN, "ssss", "SDLUser", "", VERSION, RELEASE);
  }

  int running = 1;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) running = 0;
    }
    network_update();
    SDL_SetRenderDrawColor(renderer, 30, 40, 30, 255);
    SDL_RenderClear(renderer);
    if (player_us >= 0) {
      int hx = 20;
      int tx = 20;
      for (int i = 0; i < MAX_DECK; i++) {
        if (real_game.deck[i].d_ptr == NULL) continue;
        SDL_Texture* tex = image_cache[real_game.deck[i].d_ptr->index];
        if (!tex) continue;

        float w, h;
        SDL_GetTextureSize(tex, &w, &h);
        float scale = 0.4f;

        if (real_game.deck[i].owner == player_us) {
          if (real_game.deck[i].where == WHERE_HAND) {
            SDL_FRect dest = {hx, 500, w * scale, h * scale};
            SDL_RenderTexture(renderer, tex, NULL, &dest);
            hx += w * scale * 0.8f;
          } else if (real_game.deck[i].where == WHERE_ACTIVE) {
            SDL_FRect dest = {tx, 100, w * scale, h * scale};
            SDL_RenderTexture(renderer, tex, NULL, &dest);
            tx += w * scale * 0.8f;
          }
        }
      }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  free_assets();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
