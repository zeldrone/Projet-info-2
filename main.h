#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winalleg.h>

#include <time.h>
#define ECRAN_L 1000
#define ECRAN_H 700
#define NB_SPRITE 34
#define NB_SPRITE_ENVIRONNEMENT 8
#define NB_SPRITE_BASIC 12
#define NB_SPRITE_ROACH 18
#define NB_SPRITE_AIGUILLE 28
#define NB_SPRITE_SOUFFLE 32
#define NB_SPRITE_NYDUS 34
#define NYDUS_POS 5
#define NB_CAT 6
#define STAIRS_POS 1
#define SOUFFLE_POS 4
#define SCROLL_POS 2
#define BASIC_POS 0
#define PLAYER_SPEED 10
#define NB_METIER 7
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
    float dx;
    float dy;
    t_chainB* img;
    int img_nb;
    struct souffle* next;
} t_souffle;

typedef struct player
{
    t_chainB* actuel;
    int metier_on;
    float image_refresh;
    float x;
    float y;
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
