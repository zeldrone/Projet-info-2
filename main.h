#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winalleg.h>

#include <time.h>
#define ECRAN_L 1000
#define ECRAN_H 700
#define NB_SPRITE 27
#define NB_SPRITE_ENVIRONNEMENT 2
#define NB_SPRITE_BASIC 7
#define NB_SPRITE_ROACH 13
#define NB_SPRITE_AIGUILLE 23
#define NB_SPRITE_SOUFFLE 27
#define NB_CAT 5
#define STAIRS_POS 1
#define SOUFFLE_POS 4
#define SCROLL_POS 2
#define BASIC_POS 0
#define PLAYER_SPEED 10
#define JUMP_POS 3
#define NB_METIER 5
#define AIGUILLE_POS 3


typedef struct chain_BITMAP
{
    BITMAP* bmp;
    struct chain_BITMAP* next;
} t_chainB;

typedef struct button
{
    int x1,y1;
    t_chainB* image;
    int img_nb;
    int nb_img_max;
    clock_t change;
} t_button;

typedef struct souffle
{
    int x1,y1,x2,y2;
    int angle;
    int dx,dy;
    t_chainB* img;
    int img_nb;
    struct souffle* next;
} t_souffle;

typedef struct player
{
    t_chainB* actuel;
    int metier_on;
    float image_refresh;
    int x,y;
    int dx, dy;
    int metier;
    int img_nb;
    int fall_count;
    int vie;
    int jump;
    t_souffle* souffle;
    clock_t start_anim;
    clock_t start_mov;
    int appeared;
    int angle;
    int selected;
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
//void Game_on(int lvl_nb, struct chain_BITMAP* anchor,struct chain_BITMAP* basic, struct chain_BITMAP* jump_basic, struct chain_BITMAP* stairs, struct chain_BITMAP* souffle);
