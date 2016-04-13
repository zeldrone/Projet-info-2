#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winalleg.h>
#include <math.h>
#include <time.h>
#define ECRAN_L 800
#define ECRAN_H 800
#define NB_SPRITE 19
#define NB_SPRITE_ENVIRONNEMENT 0
#define NB_SPRITE_BASIC 0
#define NB_SPRITE_SOUFFLE 0
#define NB_SPRITE_STAIRS 19
#define NB_CAT 3
#define STAIRS_POS 1
#define SOUFFLE_POS 2
#define BASIC_POS 0
#define PLAYER_SPEED 5
#define JUMP_POS 3
#define BLANC 16777215
#define ROUGE 16711680

typedef struct chain_BITMAP
{
    BITMAP* bmp;
    struct chain_BITMAP* next;
} t_chainB;
typedef struct player
{
    t_chainB* actuel;
    int x,y;
    int dx, dy;
    int metier;
    int img_nb;
    int fall_count;
    int vie;
    int jump;
    time_t start_anim;
    int angle;
   struct  player* next;
} t_ent;
typedef struct spike
{
    BITMAP* bmp;
    int x,y;
    int angle;
    struct spike* next;

}t_spike;

t_chainB* find_bitmap(t_chainB* start, int step);
void Game_on(int lvl_nb, struct chain_BITMAP* anchor,struct chain_BITMAP* basic, struct chain_BITMAP* jump_basic, struct chain_BITMAP* stairs, struct chain_BITMAP* souffle);
