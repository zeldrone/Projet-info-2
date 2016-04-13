#include "Game.h"




void init_player(t_ent* player, int input2, int input3, t_chainB* basic)
{
    player->x= input2;
    player->y= input3;
    player->actuel= basic;
    player->metier=0;
    player->img_nb=0;
    player->dx=10;
    player->dy=0;
    player->fall_count=0;
    player->vie=100;
    player->jump=0;
    player->angle=0;
}

int test_mur(t_ent* player, BITMAP* collision_map, int* high_x, int*high_y)
 {
     int i,j;
     int test=0;
     for(i=0; i<(int)(player->actuel->bmp->h/2) ;i++)
     {
         for(j=0; j<(int)(player->actuel->bmp->w/2)+player->dx; j++)
         {
            if(getpixel(collision_map, player->x+j, player->y+i)==BLANC)
            {
                test=1;
                if(high_x && high_y)
                {
                if(player->y+i>*high_y)
                {
                    *high_x=player->x+j;
                    *high_y=player->y+i;
                }
                else if (player->y+i==*high_y) *high_x=player->x+j;
                }
            }
         }
     }
     for(i=(int)(player->actuel->bmp->h/2); i<(int)(player->actuel->bmp->h);i++)
     {
         for(j=0; j<(int)(player->actuel->bmp->w/2)+player->dx; j++)
         {
            if(getpixel(collision_map, player->x+j, player->y+i)==BLANC) test=2;
         }
     }
     return test;
 }
void display(t_ent* anchor, BITMAP* buffer, BITMAP* collison_map)
{
    t_chainB* bmp;
    int test=1;
    while(anchor)
    {
        if (anchor->vie!=0)
        {
            bmp= find_bitmap(anchor->actuel, anchor->img_nb);
            pivot_sprite_v_flip(buffer,bmp->bmp ,(int)(anchor->actuel->bmp->w/2),anchor->actuel->bmp->h-1, anchor->x, anchor->y, ((int)(anchor->dx/abs(anchor->dx))-1 ? (int)PI : 2*anchor->angle)- anchor->angle+(anchor->dx/abs(anchor->dx)-1 ? 128 : 0));
            anchor=anchor->next;
        }
    }
}
int Move_players(t_chainB* basic,t_chainB* stairs,t_chainB* souffle, t_ent *player_anchor, BITMAP* collision_map, t_chainB* jump_basic )
{
    int test=1;
    int height_x, height_y;
    while(player_anchor)
    {
        player_anchor->x+=player_anchor->dx;
        player_anchor->y+=player_anchor->dy;
        player_anchor->img_nb++;
        switch(player_anchor->metier)
        {
        case 0:
            test=4;
            break;

        }
        if(player_anchor->img_nb>=test) player_anchor->img_nb=0;
        switch(test_mur( player_anchor,  collision_map, &height_x, &height_y))
        {
       case 2:
            player_anchor->dx=-player_anchor->dx;
            break;
       case 1:
           player_anchor->angle
           break;

        }
        switch (getpixel(collision_map,player_anchor->x , player_anchor->y))
        {
        case BLANC:
            player_anchor->dx= PLAYER_SPEED*((player_anchor->dx/(abs(player_anchor->dx) ? player_anchor->dx: 1)) ? player_anchor->dx/abs(player_anchor->dx) : 1) ;
            break;
        case 0:
            if(player_anchor->jump==0)
            {
                player_anchor->jump=1;
                player_anchor->img_nb=0;
                player_anchor->actuel=jump_basic;
                player_anchor->dx=5;
                player_anchor->dy=-10;
            }
            player_anchor->dx--;
            player_anchor->dy++;
            break;
        case ROUGE:
            player_anchor->vie-=2;
            break;


        }
        player_anchor=player_anchor->next;
    }
}

/*int lvl_loader(BITMAP* buffer, BITMAP* collision_map, t_ent* player_anchor, int lvl_nb, t_chainB* basic, t_chainB* anchor, t_spike* spike_anchor, int* tot_play, int* nb_spikes)
{
    FILE* lvl_file;
    int input1, input2, input3, input4,input5,input6,input7, i,j;
    char mot[30];
    sprintf(mot, "TXT/lvl_%d", lvl_nb);
    lvl_file=fopen(mot, "r");
    fscanf(lvl_file, "%d", tot_play);
    buffer=create_bitmap(SCREEN_W, SCREEN_H);
    collision_map=create_bitmap(SCREEN_W, SCREEN_H);
    fscanf(lvl_file, "%d", &input1);
    fscanf(lvl_file, "%d", &input2);
    fscanf(lvl_file, "%d", &input3);
    for(i=0; i<input1; i++)
    {
        init_player(player_anchor, input2, input3, basic);
        if(i!=input1-1)
        {
            player_anchor->next= (t_ent*) malloc(sizeof(t_ent));
            player_anchor=player_anchor->next;
        }
    }
    blit(anchor->bmp, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    fscanf(lvl_file, "%d", &input1);
    i=0;
    for(i=0; i<input1; i++) //lecture des murs
    {
        fscanf(lvl_file, "%d", &input2);
        fscanf(lvl_file, "%d", &input3);
        fscanf(lvl_file, "%d", &input4);
        fscanf(lvl_file, "%d", &input5);
        rectfill(collision_map, input2, input3, input4, input5, makecol(255,255,255));
        masked_blit(find_bitmap(anchor, 1), buffer, 0,0, input2, input3, abs(input4-input2), abs(input5-input3));
    }
    fscanf(lvl_file, "%d", nb_spikes);
    i=0;
    for(i=0; i<nb_spikes; i++) //lecture des spike
    {
        fscanf(lvl_file, "%d", &input2);
        fscanf(lvl_file, "%d", &input3);
        fscanf(lvl_file, "%d", &input4);
        fscanf(lvl_file, "%d", &input5);
        spike_anchor->angle=(int)((90*(1-1/2^((input3-input5)/(input2-input4))))*(256/360));
        spike_anchor->bmp=flame;
        spike_anchor->x=input3+(int)flame->bmp->w*(sin(angle*(360/256))/2);
        spike_anchor->y=
        triangle(collision_map, input2, input3, input4, input5, input3+(int)flame->bmp->w*(sin(angle*(360/256))/2)+flame->bmp->w/2,flame->bmp->h+input2-flame->bmp->w*(sin(angle*(360/256))/2)+flame->bmp->w/2, makecol(255,0,0));
        rotate_sprite(buffer,flame->bmp,input3+(int)flame->bmp->w*(sin(angle*(360/256))/2),flame->bmp->h+input2-flame->bmp->w*(sin(angle*(360/256))/2), angle);
    }

    fscanf(lvl_file, "%d", &input1);
    i=0;
    for(i=0; i<input1; i++) //lecture des spéciaux
    {
        fscanf(lvl_file, "%d", &input2);
        switch(input2)
        {

        }
    }
}*/

void Game_on(int lvl_nb, t_chainB* anchor,t_chainB* basic,t_chainB* jump_basic, t_chainB* stairs, t_chainB* souffle)
{
    BITMAP* collision_map, *buffer;
    t_ent player_anchor;
    t_ent buff;
    t_spike spike_anchor;
    time_t first, test, i;
    int game=1, players_nb=0, tot_play=0,nb_spikes=0;
    //lvl_loader(buffer, collision_map, &player_anchor, lvl_nb, basic, anchor, &spike_anchor, &tot_play, &nb_spikes);
//    level_load(lvl_nb, collision_map, buffer)
    first=time(NULL);
    while (game)
    {
        test=time(NULL);
        if(players_nb<tot_play)players_nb=difftime(test, first)/5;
        buff.actuel=anchor;
        for(i=0; i<players_nb; i++)
        {
            Move_players(basic, stairs, souffle,&player_anchor, collision_map, jump_basic );
        }
        //if(difftime(test,first)%2) for(i=0; i<nb_spikes)

    }

}END_OF_FUNCTION();

t_chainB* find_bitmap(t_chainB* start, int step)
{
    int i;
    for(i=0; i<step; i++)
    {
        start=start->next;
    }
    return start;
}

int load_all_bitmap(t_chainB* anchor,t_chainB **basic_point,t_chainB **stairs_point,t_chainB **souffle_point)
{
 char mot[50];

 int i;
 for(i=0; i<NB_SPRITE; i++)
 {
     if (i<=NB_SPRITE_ENVIRONNEMENT)
     {
         switch(i)
         {
         case 0:
            sprintf(mot, "Images/fond.bmp");
            break;
         case 1:
            sprintf(mot, "Images/mur.bmp");
            break;
         case 2:
            sprintf(mot, "Images/spikes.bmp");
            break;
         }
     }
     else if(i<=NB_SPRITE_BASIC) sprintf(mot, "Images/basic%d.bmp", i);
     else if(i<= NB_SPRITE_STAIRS) sprintf(mot, "Images/stairs%d.bmp", i-NB_SPRITE_BASIC);
     else if(i<= NB_SPRITE_SOUFFLE) sprintf(mot, "Images/souffle%d.bmp", i-NB_SPRITE_STAIRS);
     if(i==NB_SPRITE_BASIC) *basic_point=anchor;
     if(i==NB_SPRITE_STAIRS) *stairs_point= anchor;
     if(i==NB_SPRITE_SOUFFLE) *souffle_point= anchor;
     anchor->bmp=load_bitmap(mot,NULL);
     anchor->next= (t_chainB*) malloc(sizeof(t_chainB));
     anchor=anchor->next;
 }
}
int allegro_demarre()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(16);
    return (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,800,0,0));
}
int allegro_scan_string(char mot[], int window_size_w, int window_size_h,int window_color, int text_color, const char* question,FONT* font_ask)
{
    //0 déclaration de variables
    BITMAP* zone;
    BITMAP* fond, *save_fond;
    int a=0;
    int key_allegro;
    char key_ascii;
    int i=0;
    mot[0]='\0';

    //1 initialisation
    fond= create_bitmap(SCREEN_W, SCREEN_H);
    save_fond= create_bitmap(SCREEN_W, SCREEN_H);
    zone= create_bitmap(window_size_w, window_size_h);
    blit(screen, fond,0,0,0,0, SCREEN_W, SCREEN_H);
    blit(fond, save_fond,0,0,0,0, SCREEN_W, SCREEN_H);
    clear_to_color(zone, window_color);
    textprintf_ex(zone, font_ask, 0, 0, text_color,-1, "%s", question);
    draw_sprite(fond, zone,(int)(( SCREEN_W-window_size_w)/2), (int)(( SCREEN_H-window_size_h)/2));// on affiche a l'écran
    blit(fond, screen,0,0,0,0, SCREEN_W, SCREEN_H);
    rest(200);// pause pour éviter les interférences
    while(!key[KEY_ENTER])
    {
        if (key[KEY_ESC])// sortie brutale
        {
            blit(save_fond, screen,0,0,0,0, SCREEN_W, SCREEN_H);
            return 1;
        }
        if (key[KEY_BACKSPACE])
        {
            clear_to_color(zone, window_color);
            textprintf_ex(zone, font_ask, 0, 0, text_color,-1, "%s", question);
            blit(save_fond, fond, 0,0,0,0, SCREEN_W, SCREEN_H);
            draw_sprite(fond, zone,(int)(( SCREEN_W-window_size_w)/2), (int)(( SCREEN_H-window_size_h)/2));// on affiche a l'écran
            blit(fond, screen,0,0,0,0, SCREEN_W, SCREEN_H);
            a=0;
            mot[0]='\0';
        }
        if (keypressed())
        {
            key_allegro=readkey();// récuperation de la touche
            key_ascii= key_allegro & 0xff; // récupération de son code ASCII

            if((key_ascii >= 32) && (key_ascii <= 126))// si la touche est utile
            {
                    mot[i]= key_ascii;// on entre le caractère
                    mot[i+1]='\0'; // on place le \0
                    // on affcihe la chaine
                    clear_to_color(zone, window_color);
                    textprintf_ex(zone, font_ask, 0, 0, text_color,-1, "%s", question);
                    textprintf_ex(zone, font_ask, 0, 2*(text_height(font)+5), text_color,-1, "%s", mot);
                    //textprintf_ex(zone, font, i*text_length(font, "O"), 2*(text_height(font)+5), text_color,-1, "%c", mot[i]);
                    blit(save_fond, fond, 0,0,0,0, SCREEN_W, SCREEN_H);
                    draw_sprite(fond, zone,(int)(( SCREEN_W-window_size_w)/2), (int)(( SCREEN_H-window_size_h)/2));// on affiche a l'écran
                    blit(fond, screen,0,0,0,0, SCREEN_W, SCREEN_H);
                    i++;
            }
            clear_keybuf();
        }
    }

    mot[i]='\0';
    return 0; //sortie
}

int menu(t_chainB* anchor,t_chainB *basic,t_chainB *stairs,t_chainB *souffle, t_chainB* jump_basic)
{
    BITMAP* fond_menu;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    FILE* level_save;
    FONT* hobbit=NULL;
    int lvl_nb;
    fond_menu= load_bitmap("Images/fond_menu.bmp",NULL);
    char input[50];
    hobbit=load_font("Piksel.fnt",NULL,NULL);
    level_save=fopen("TXT/level_save.txt", "r");
    fscanf(level_save,"%d", &lvl_nb);
    if(!hobbit) printf("echec chargement font\n");
    blit(fond_menu, buffer, 0,0,0,0, SCREEN_W, fond_menu->h);
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 30,40, makecol(255,255,255), 0, "Es-ce que ca marche?");

    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    allegro_scan_string(input,768, 192, makecol(255,0,255), makecol(255,255,255), "Quel est votre choix?", font);

    if(!strcmp(input, "jouer"))
    {
       Game_on(lvl_nb, anchor, basic,jump_basic, stairs, souffle);
    }

    destroy_bitmap(fond_menu);
    destroy_bitmap(buffer);
    return 0;
} END_OF_FUNCTION();
int main()
{
    //if(allegro_demarre()) printf("ooops\n");
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(16);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000,700,0,0);
    t_chainB* waypt[NB_CAT];
    t_chainB anchor;
    //load_all_bitmap(&anchor, &(waypt[BASIC_POS]), &(waypt[STAIRS_POS]), &(waypt[SOUFFLE_POS]));
    while(menu(&anchor, waypt[BASIC_POS], waypt[STAIRS_POS], waypt[SOUFFLE_POS], waypt[JUMP_POS]));
    return 0;
} END_OF_MAIN();
