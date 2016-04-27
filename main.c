#include "Game.h"
#include <math.h>
double distance(int x1,int y1,int x2,int y2)
{
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

void find_start_point_pente(int *start_x, int *start_y, int* x,float* y,float pente, BITMAP* collision_map)
{
    if(pente!=(int)pente)
    {
        while(getpixel(collision_map,*x,*y)==BLANC)
        {
            if(pente<0)(*x)--;
            else (*x)++;
            (*y)-=(int)pente;
        }
        if(pente<0) (*x)-=4;
        else (*x)+=4;
        *start_x=*x;
        *start_y=*y;
    }

}
BITMAP* create_rectangle(int distance, int width, int color)
{
    BITMAP* buffer;
    buffer=create_bitmap(distance, width);
    clear_to_color(buffer, color);
    return buffer;
}
int col_around(BITMAP* collision_map, int x, int y, int col)
{
    int test=0;
    if(getpixel(collision_map, x, y+1)==col || getpixel(collision_map, x, y-1)==col  || getpixel(collision_map, x+1, y)==col  || getpixel(collision_map, x-1, y)==col ) test=1;
    return test;
}
int find_angle_point(BITMAP* collision_map, int* x,int* y, int col)
{
    int compteur1, compteur2;
    int save_x=*x, save_y=*y;
    int dx=0;
    int dy=0;
    if(getpixel(collision_map, save_x+1, save_y+1)==col  && col_around(collision_map, save_x+1, save_y+1, 0))
    {
        save_x++;
        save_y++;
        dx=1;
        dy=1;
    }
    else if(getpixel(collision_map, save_x-1, save_y+1)==col  && col_around(collision_map, save_x-1, save_y+1, 0))
    {
        save_x--;
        save_y++;
        dx=-1;
        dy=-1;
    }
    else if(getpixel(collision_map, save_x-1, save_y-1)==col  && col_around(collision_map, save_x-1, save_y-1, 0))
    {
        save_x--;
        save_y--;
        dy=-dy;
        dx=-1;
    }
    else if(getpixel(collision_map, save_x+1, save_y-1)==col  && col_around(collision_map, save_x+1, save_y-1, 0))
    {
        save_x++;
        save_y--;
        dx=1;
        dy=-1;
    }
    else  if(getpixel(collision_map, save_x, save_y+1)==col  && col_around(collision_map, save_x, save_y+1, 0))
    {
        save_y++;
        dy=1;
    }
    else if((getpixel(collision_map, save_x, save_y-1)==col  && col_around(collision_map, save_x, save_y-1, 0)))
    {
        save_y--;
        dy=-1;
    }
    else if(getpixel(collision_map, save_x+1, save_y)==col  && col_around(collision_map, save_x+1, save_y, 0))
    {
        save_x++;
        dx=1;
    }
    else if((getpixel(collision_map, save_x-1, save_y)==col  && col_around(collision_map, save_x-1, save_y, 0)))
    {
        save_x--;
        dx=-1;
    }

    while(distance(*x,*y, save_x, save_y)<20 && save_y<collision_map->h && save_x<collision_map->w && save_x>0 && save_y>0)
    {

        if((getpixel(collision_map, save_x+dx, save_y+dy)==col  && col_around(collision_map, save_x+dx, save_y+dy, 0)));
        else
        {
            if(dy==0)
            {
                dy=1;
                if (getpixel(collision_map, save_x-dx, save_y+dy)==col  && col_around(collision_map, save_x-dx, save_y+dy, 0))
                {
                    dx=-dx;
                }
                else if (getpixel(collision_map, save_x+dx, save_y+dy)==col  && col_around(collision_map, save_x+dx, save_y+dy, 0));
                else if (getpixel(collision_map, save_x, save_y+dy)==col  && col_around(collision_map, save_x, save_y+dy, 0)) dx=0;
                else
                {
                    dy=-1;
                    if (getpixel(collision_map, save_x-dx, save_y+dy)==col  && col_around(collision_map, save_x-dx, save_y+dy, 0))
                    {
                        dx=-dx;
                    }
                    else if (getpixel(collision_map, save_x+dx, save_y+dy)==col  && col_around(collision_map, save_x+dx, save_y+dy, 0));
                    else if (getpixel(collision_map, save_x, save_y+dy)==col  && col_around(collision_map, save_x, save_y+dy, 0)) dx=0;
                }
            }
            else if(dx==0)
            {
                dx=1;
                if (getpixel(collision_map, save_x+dx, save_y-dy)==col  && col_around(collision_map, save_x+dx, save_y-dy, 0))
                {
                    dy=-dy;
                }
                else if (getpixel(collision_map, save_x+dx, save_y+dy)==col  && col_around(collision_map, save_x+dx, save_y+dy, 0));
                else if (getpixel(collision_map, save_x+dx, save_y)==col  && col_around(collision_map, save_x+dx, save_y, 0)) dy=0;
                else
                {
                    dx=-1;
                    if (getpixel(collision_map, save_x+dx, save_y-dy)==col  && col_around(collision_map, save_x+dx, save_y-dy, 0))
                    {
                        dy=-dy;
                    }
                    else if (getpixel(collision_map, save_x+dx, save_y+dy)==col  && col_around(collision_map, save_x+dx, save_y+dy, 0));
                    else if (getpixel(collision_map, save_x+dx, save_y)==col  && col_around(collision_map, save_x+dx, save_y, 0)) dy=0;
                }
            }
            else if (getpixel(collision_map, save_x-dx, save_y+dy)==col  && col_around(collision_map, save_x-dx, save_y+dy, 0))
            {
                dx=-dx;
            }
            else if((getpixel(collision_map, save_x+dx, save_y-dy)==col  && col_around(collision_map, save_x+dx, save_y-dy, 0))&& dx!=0)
            {
                dy=-dy;
            }
            else if((getpixel(collision_map, save_x-dx, save_y)==col  && col_around(collision_map, save_x-dx, save_y, 0)))
            {
                dx=-dx;
                dy=0;
            }
            else if((getpixel(collision_map, save_x+dx, save_y)==col  && col_around(collision_map, save_x+dx, save_y, 0)))
            {
                dy=0;
            }
            else if((getpixel(collision_map, save_x, save_y-dy)==col  && col_around(collision_map, save_x, save_y-dy, 0))&& dx!=0)
            {
                dx=0;
                dy=-dy;
            }
            else if((getpixel(collision_map, save_x, save_y+dy)==col  && col_around(collision_map, save_x, save_y+dy, 0)))
            {
                dx=0;
            }
        }
        save_x+=dx;
        save_y+=dy;

    }
    *x=save_x;
    *y=save_y;
    return 0;
}
float determine_angle(int x, float y, BITMAP* collision_map,double pente, double angle, int* test)
{
    int x1=x, y1=y;

    if(find_angle_point(collision_map, &x1,&y1, BLANC)) return pente ;
    printf("%f  %f\n",atan2(y1-y, x1-x)*256/(2*M_PI),fabs((atan2(y1-y, x1-x)*256/(2*M_PI)-angle)));
    if(fabs((atan2(y1-y, x1-x)*256/(2*M_PI)-angle))>48)
    {
        *test=0;
        return 0;
    }

    else
    {
        printf(" %f\n",(y1-y)/(x1-x) );
        system("pause");
        return (y1-y)/(x1-x);
    }
}
void build_souffle(t_ent* anchor, float fin_x,float fin_y,t_chainB* anim_souffle, BITMAP* collision_map)
{
    t_souffle* buffer=(t_souffle*)malloc(sizeof(t_souffle));
    int test=1;
    int x=anchor->x;
    float y=0;
    y+=anchor->y-anchor->actuel->bmp->h/2;
    int start_x=anchor->x;
    float compteur1;
    int start_y=anchor->y-anchor->actuel->bmp->h/2;;
    float pente=0;
    float compteur=0;
    int nb_img=0;

    anchor->souffle=buffer;
    while (compteur<700  && test)
    {
        compteur1=0;
        while(getpixel(collision_map, x,y)!=BLANC && getpixel(collision_map, x,y)!=BLEU && x>0 && x<collision_map->w && y>0 && y<collision_map->h && compteur1<700-compteur)
        {
            if((fin_x-start_x)>0)
            {
                x++;
                if(pente==0)y=y+((fin_y-start_y)/(fin_x-start_x));
                else y+=pente;
            }
            else if(fin_x-start_x<0)
            {
                x--;
                if(pente==0)y=y-((fin_y-start_y)/(fin_x-start_x));
                else y-=pente;
            }
            else y--;
            compteur1=distance(start_x, start_y, x,y);
        }
        if(!(x>0 && x<collision_map->w && y>0 && y<collision_map->h))test=0;
        compteur+=compteur1;
        buffer->x1=start_x;
        buffer->y1=start_y;
        buffer->x2=x;
        buffer->y2=y;
        nb_img++;
        if(nb_img>=5) nb_img=0;
        buffer->img=anim_souffle;
        buffer->img_nb= nb_img;
        buffer->angle= 256/(2*M_PI)*atan2((fin_y-start_y),(fin_x-start_x));
        pivot_sprite(collision_map, create_rectangle(distance(buffer->x1, buffer->y1, buffer->x2, buffer->y2), 20, VERT), buffer->x1, buffer->y1, 0, 10, itofix(buffer->angle));
        buffer->dx=PLAYER_SPEED*(fin_y-start_y)/(fin_x-start_x);
        buffer->dy=PLAYER_SPEED*(fin_x-start_x)/(fin_y-start_y);
        printf("yo maggle  %f\n", compteur);
        if(compteur<700 && test)
        {
        compteur1=fin_x;
        pente=determine_angle(x,y, collision_map,(fin_y-start_y)/(compteur1-start_x), buffer->angle, &test);
        fin_x= x+ (fin_x-start_x>0 ? 1: -1)*(700-compteur)/sqrt(1+pow(determine_angle(x,y, collision_map,(fin_y-start_y)/(fin_x-start_x), buffer->angle, &test),2));
        if(fin_x!=x)fin_y= y+ (fin_x-x)*(700-compteur)*determine_angle(x, y, collision_map,(fin_y-start_y)/(compteur1-start_x), buffer->angle, &test);
        else printf("HELP! I NEED SOMEBODY HELP!\n");
        find_start_point_pente(&start_x, &start_y, &x,&y, pente, collision_map);

            buffer->next= (t_souffle*)malloc(sizeof(t_souffle));
            buffer=buffer->next;
        }
        else buffer->next=NULL;
    }

}

BITMAP* barre_vie(t_ent* player)
{
    BITMAP* vie=create_bitmap(player->actuel->bmp->w, 7);
    clear_to_color(vie, ROUGE);
    printf("\n\n\n\n\n\n\n%d     %d    %d\n\n\n\n",(player->vie*vie->w/100), player->vie, vie->w);
    rectfill(vie,0,0,(player->vie*vie->w/100), 7, makecol(0,255,0));
    return vie;
}
void dess_viseur(BITMAP *page,int x, int y, int col)
{
    circle(page,x,y,5,col);
    line(page,x-5,y-5,x-2,y-2,col);
    line(page,x+5,y-5,x+2,y-2,col);
    line(page,x-5,y+5,x-2,y+2,col);
    line(page,x+5,y+5,x+2,y+2,col);
}



int champ_aiguillon(int x1,int y1,int x2,int y2) // regarde si le point choisi quand on vise est bien dans le champ de "vision" de l'aiguillon
{
    int ok=0;
    if ((fabs(x2-x1)>=fabs(y2-y1))&&(y2<=y1)) ok=1;
    return ok;
}
void display_buttons(t_button buttons[NB_METIER],BITMAP* buffer)
{
    int i=0;
    if(mouse_needs_poll()) poll_mouse();
    for(i=0; i<NB_METIER-1; i++)
    {
        if(mouse_x>buttons[i].x1 && mouse_x<buttons[i].x1+buttons[i].image->bmp->w && mouse_y>buttons[i].y1)
        {
            if( clock()>buttons[i].change )
            {
                buttons[i].img_nb++;
                if(buttons[i].img_nb==buttons[i].nb_img_max)
                {
                    buttons[i].img_nb=0;
                    if(i==2)buttons[i].img_nb=1;
                }
                buttons[i].change=clock()+0.1*CLOCKS_PER_SEC;
            }
        }
        else  buttons[i].img_nb=0;
        printf("    %d", buttons[i].img_nb);
        if(i==2 && buttons[i].img_nb>=1)
        {
            draw_sprite(buffer, buttons[i].image->bmp, buttons[i].x1, buttons[i].y1);
            pivot_sprite(buffer,find_bitmap(buttons[i].image, buttons[i].img_nb)->bmp, buttons[i].x1+buttons[i].image->bmp->w/2, buttons[i].y1, 0, 15, itofix(-64));
        }
        else draw_sprite(buffer, find_bitmap(buttons[i].image, buttons[i].img_nb)->bmp, buttons[i].x1, buttons[i].y1);
    }
    printf("\n");
}
void init_buttons(t_button button[NB_METIER], t_chainB* basic,t_chainB* roach, t_chainB* aiguille, t_chainB* souffle )
{
    button[0].image=basic;
    button[0].img_nb=0;
    button[0].nb_img_max=4;
    button[0].change= clock();
    button[0].x1=0;
    button[0].y1=SCREEN_H-button[0].image->bmp->h;
    button[1].image=roach;
    button[1].img_nb=0;
    button[1].nb_img_max=6;
    button[1].change= clock();
    button[1].x1=button[0].image->bmp->w+3;
    button[1].y1=SCREEN_H-button[1].image->bmp->h;
    button[2].image=aiguille;
    button[2].img_nb=0;
    button[2].nb_img_max=3;
    button[2].change= clock();
    button[2].x1=button[1].x1+button[1].image->bmp->w+3;
    button[2].y1=SCREEN_H-button[2].image->bmp->h;
    button[3].image=souffle;
    button[3].img_nb=0;
    button[3].nb_img_max=4;
    button[3].change= clock();
    button[3].x1=button[2].x1+button[2].image->bmp->w+3;
    button[3].y1=SCREEN_H-button[3].image->bmp->h;
}

void destroy_chain_member(t_ent* player_anchor, int nb)
{
    int i;
    t_ent *buff2;
    for(i=0; i<nb+1; i++)
    {

        if(i==nb)
        {
            printf("HIIIIII\n\n");
            buff2->next=player_anchor->next;
            printf("HIIIIII22\n\n");
            //free(player_anchor);
        }

        if(i==nb-1) buff2=player_anchor;
        player_anchor=player_anchor->next;
    }

}
void scrolling(int* pos_blit_x,int* pos_blit_y, t_chainB* scrolling_mouse, BITMAP* buffer, BITMAP* collision_map)
{
    if(mouse_x>SCREEN_W-20 && *pos_blit_x+SCREEN_W+1<collision_map->w)
    {
        (*pos_blit_x)++;
        draw_sprite(buffer, scrolling_mouse->bmp, mouse_x+*pos_blit_x, mouse_y+*pos_blit_y);
    }
    else if(mouse_x<20 && *pos_blit_x-1>0)
    {
        (*pos_blit_x)--;
        draw_sprite(buffer, scrolling_mouse->next->bmp, mouse_x+*pos_blit_y, mouse_y+*pos_blit_y);
    }
    if(mouse_y>SCREEN_H-150 && mouse_y<SCREEN_H-100 && *pos_blit_y+SCREEN_H-150<collision_map->h)
    {
        (*pos_blit_y)++;
        draw_sprite(buffer, scrolling_mouse->bmp, mouse_x+*pos_blit_x, mouse_y+*pos_blit_y);
    }
    else if(mouse_y<20 && *pos_blit_y-1>0)
    {
        (*pos_blit_y)--;
        draw_sprite(buffer, scrolling_mouse->next->bmp, mouse_x+*pos_blit_x, mouse_y+*pos_blit_y);
    }

}
int get_sens(t_ent* player) // return 0 si dx>0, 1 si dx<0
{
    int sens;
    if (player->dx>0) sens=0;
    if (player->dx<0) sens=1;
    return sens;
}

int mouse_check(t_ent* player, t_ent* player_anchor, int pos_blit_x,int pos_blit_y, BITMAP* collision_map, t_button buttons[NB_METIER])
{
    int test=0;
    int i;
    t_ent* buffer= player_anchor;
    if(mouse_needs_poll())poll_mouse();
    if(player && mouse_b&1)
    {
        if(mouse_y>SCREEN_H-150)
        {
            if(mouse_b&1)
            {
                for(i=0; i<NB_METIER; i++)
                {
                    if(mouse_x>buttons[i].x1 && mouse_x<buttons[i].x1+buttons[i].image->bmp->w)
                    {
                        while(buffer)
                        {
                            if(buffer->selected)
                            {
                                buffer->metier=i;
                                buffer->selected=0;
                                buffer->actuel= buttons[i].image;
                                switch(i)
                                {
                                case 0:
                                    buffer->metier_on=0;
                                    buffer->dx=(buffer->dx ? buffer->dx/abs(buffer->dx): (buffer->jump? buffer->jump : 1))*PLAYER_SPEED;
                                    buffer->image_refresh=0.1;
                                    break;
                                case 1:
                                    buffer->metier_on=0;
                                    buffer->dx= (buffer->dx ? buffer->dx/abs(buffer->dx): (buffer->jump? buffer->jump : 1))*PLAYER_SPEED/2;
                                    break;
                                case 3:
                                    buffer->angle=0;
                                    buffer->jump=0;
                                case 2:
                                    buffer->dx=0;
                                    mouse_b=mouse_b^1;
                                    buffer->metier_on=2;
                                }
                            }
                            buffer=buffer->next;
                        }
                    }
                }
            }
        }
        if( mouse_x+pos_blit_x<player->x+player->actuel->bmp->w/2 && mouse_x+pos_blit_x>player->x-player->actuel->bmp->w/2 && mouse_y+pos_blit_y>player->y-player->actuel->bmp->h && mouse_y+pos_blit_y< player->y)
        {
            test=1;
            while(player_anchor)
            {
                player_anchor->selected=0;
                player_anchor=player_anchor->next;
            }
            player->selected=1;
        }
    }
    return test;
}
void change_img(t_ent* player_anchor)
{
    int test;
    player_anchor->img_nb++;
    switch(player_anchor->metier)
    {
    case 0:
        test=4;
        break;
    case 1:
        if(!player_anchor->metier_on) test=3;
        else test=6;
        break;
    case 2:
        if(player_anchor->metier_on==2) test=0;
        else if (player_anchor->metier_on<75) test=2;
        else if(player_anchor->metier_on<109) test=3;
        else if (player_anchor->metier_on<135) test=4;
        else if (player_anchor->metier_on<172) test=5;
        else if  (player_anchor->metier_on<200) test=6;
        else if (player_anchor->metier_on<255) test=7;
        else if (player_anchor->metier_on<295) test=8;
        else if (player_anchor->metier_on<335) test=9;
        else if (player_anchor->metier_on<373) test=10;
        break;
    case 3:
        test=4;
        break;
    }
    if(player_anchor->img_nb>=test)
    {
        player_anchor->img_nb=0;
        if(test==6 && player_anchor->metier==1) player_anchor->img_nb=3;
        if(player_anchor->metier==2)player_anchor->img_nb=(test-1>0 ? test-1: test);
    }
}
void creuser(BITMAP* coll_map,t_ent *player, BITMAP* front)
{
    if (!get_sens(player))
    {
        player->dx=5;
        rectfill(coll_map,player->x+player->actuel->bmp->w/2,player->y,player->x+player->actuel->bmp->w/2+5,player->y-70,makecol(0,0,0));
        rectfill(front,player->x+player->actuel->bmp->w/2,player->y,player->x+player->actuel->bmp->w/2+5,player->y-70,makecol(255,0,255));

    }
    if (get_sens(player))
    {
        player->dx=-2;
        rectfill(coll_map,player->x-player->actuel->bmp->w/2,player->y,player->x-player->actuel->bmp->w/2-5,player->y-70,makecol(0,0,0));
        rectfill(front,player->x-player->actuel->bmp->w/2,player->y,player->x-player->actuel->bmp->w/2-5,player->y-70,makecol(255,0,255));

    }

}

int distance_y_to_color(int x, int y, BITMAP* collision_map, int color )
{
    int compteur1=0, compteur2=0;
    int save_y=y;
    while (getpixel(collision_map, x, save_y)!=color)
    {
        save_y--;
        compteur1++;
        if(save_y<=0)
        {
            break;
        }
    }
    while (getpixel(collision_map, x, y)!=color)
    {
        y++;
        compteur2++;
        if(y>=SCREEN_H)
        {
            break;
        }
    }
    printf(" \n\nHELLLLLLOOOOOO %d\n",(compteur1<=compteur2 ? compteur1 : compteur2 ));
    return (compteur1<=compteur2 ? compteur1 : compteur2);
}
void init_player(t_ent* player, int input2, int input3, t_chainB* basic)
{
    player->selected=0;
    player->x= input2;
    player->y= input3;
    player->actuel= basic;
    player->metier=0;
    player->img_nb=0;
    player->dx=-PLAYER_SPEED;
    player->dy=0;
    player->fall_count=0;
    player->vie=100;
    player->jump=0;
    player->angle=0;
    player->start_anim= 0;
    player->appeared=0;
    player->metier_on=0;
    player->image_refresh=0.1;
    player->souffle=NULL;
}
void    level_load(int lvl_nb,BITMAP** collision_map, int* tot_players, t_ent** player_anchor, t_chainB* basic, int* goal_x, int* goal_y)
{
    printf("yolo\n");
    int i=0;
    int coord_x=0, coord_y=0;
    t_ent* buff;
    switch(lvl_nb)
    {
    case 1:
        *tot_players=2;
        coord_x=170;
        coord_y=200;
        *goal_x=
        *collision_map=load_bitmap("Images/yolo.bmp", NULL);

        break;
    }
    *player_anchor=(t_ent*)malloc(sizeof(t_ent));
    buff=*player_anchor;
    for(i=0; i<(*tot_players); i++)
    {

        init_player(buff, coord_x, coord_y, basic);

        if(i+1<*tot_players)
        {
            (buff)->next=(t_ent*)malloc(sizeof(t_ent));
            buff=buff->next;
        }
        else buff->next=NULL;

    }

}


int test_mur(t_ent* player, BITMAP* collision_map, int* high_x, int*high_y)
{
    int i,j;
    int test=0;
    for(i=1; i<(int)(player->actuel->bmp->h/2) ; i++)
    {
        for(j= (player->dx>0? player->actuel->bmp->w/2-10 : (-1)*player->actuel->bmp->w/2); j< (player->dx>0? player->actuel->bmp->w/2 : (-1)*player->actuel->bmp->w/2+10); j++)
        {
            if(getpixel(collision_map, player->x+j, player->y-i)==BLANC  || getpixel(collision_map, player->x+j, player->y-i)==BLEU)
            {
                test=1;
                if(high_x!=NULL && high_y!=NULL)
                {
                    if(player->y-i<*high_y)
                    {
                        (*high_x)=player->x+j;
                        (*high_y)=player->y-i;
                    }
                    else if ((player->y-i==*high_y) && player->dx!=0) *high_x=player->x+j;
                }
            }
        }
    }
    for(i=(int)(player->actuel->bmp->h/2); i<(int)(player->actuel->bmp->h); i++)
    {
        for(j=(player->dx>0? player->actuel->bmp->w/2-10 : (-1)*(player->actuel->bmp->w/2-player->dx)); j< (player->dx>0? player->actuel->bmp->w/2+player->dx :  (-1)*player->actuel->bmp->w/2+10); j++)
        {
            if(getpixel(collision_map, player->x+j, player->y-i)==BLANC) test=2;
            if(getpixel(collision_map, player->x+j, player->y-i)==BLEU)
            {
                test=3;
                break;
            }
        }
    }
    return test;
}
void display_players(t_ent* anchor, BITMAP* buffer, BITMAP* collison_map, BITMAP* arrow, t_chainB* anim_souffle, int pos_blit_x, int pos_blit_y)
{
    t_chainB* bmp;
    int test=1;
    int col;
    int x=0,y=0;
    int points[8];
    while(anchor)
    {
        if ((anchor->vie>0)&&(anchor->appeared!=0))
        {
            if(anchor->metier_on==2)
            {
                switch(anchor->metier)
                {

                case 2:
                    pivot_sprite(buffer, anchor->actuel->bmp, anchor->x, anchor->y, anchor->actuel->bmp->w/2, anchor->actuel->bmp->h, itofix(0));
                    if (getpixel(collison_map,mouse_x,mouse_y)==BLANC) col=makecol(51,204,0); // VERT
                    if (getpixel(collison_map,mouse_x,mouse_y)!=BLANC) col=ROUGE;
                    if (distance(anchor->x,anchor->y,mouse_x,mouse_y)>370) col=ROUGE;
                    if (!champ_aiguillon(anchor->x,anchor->y,mouse_x,mouse_y)) col=ROUGE;
                    line(buffer,anchor->x,anchor->y,mouse_x+pos_blit_x,mouse_y+pos_blit_y,col);
                    dess_viseur(buffer,mouse_x+pos_blit_x,mouse_y+pos_blit_y,col);
                    if(mouse_b&1 && col==makecol(51,204,0))
                    {
                        anchor->angle=(255/(2*M_PI))*atan2(mouse_y+6-(anchor->y),mouse_x-(anchor->x));
                        int points[8]= {anchor->x,anchor->y, anchor->x,anchor->y-11, mouse_x+pos_blit_x,mouse_y+pos_blit_y-6, mouse_x+pos_blit_x,mouse_y+pos_blit_y};
                        polygon(collison_map,4,points,makecol(0,0,255)); // BLEU
                        rectfill(collison_map,anchor->x-50,anchor->y,anchor->x+50,anchor->y-10,makecol(0,0,255));
                        rectfill(collison_map,anchor->x-20,anchor->y,anchor->x+20,anchor->y-20,makecol(0,0,255));
                    }
                    break;
                case 3:
                    col=makecol(51,204,0);
                    pivot_sprite(buffer, anchor->actuel->bmp, anchor->x, anchor->y, anchor->actuel->bmp->w/2, anchor->actuel->bmp->h, itofix(0));
                    x=mouse_x+pos_blit_x;
                    y=mouse_y+pos_blit_y;
                    if(!(int)((mouse_y+pos_blit_y-anchor->y)/(mouse_x+pos_blit_x-anchor->x))) y=anchor->y-anchor->actuel->bmp->h/2;
                    /*if(distance(anchor->x, anchor->y, mouse_x,mouse_y)>100)
                    {
                        x=anchor->x+(mouse_x-anchor->x>0? 1 : -1)*100/sqrt(1+(pow((mouse_y-anchor->y)/(mouse_x-anchor->x? anchor->x-mouse_x:1),2));
                        y=anchor->y+((x-anchor->x)*(anchor->y-mouse_y))/(anchor->x-mouse_x ? anchor->x-mouse_x:1);
                    }*/
                    if(mouse_y>anchor->y)col=ROUGE;
                    line(buffer,anchor->x,anchor->y-anchor->actuel->bmp->h/2,x,y,col);
                    dess_viseur(buffer,x,y,col);
                    if(mouse_b&1 && col==makecol(51,204,0))
                    {
                        anchor->metier_on=1;
                        build_souffle(anchor,x,y, anim_souffle, collison_map);
                    }

                    break;
                }
            }
            else if(anchor->metier==2)
            {
                pivot_sprite(buffer, anchor->actuel->bmp, anchor->x, anchor->y, anchor->actuel->bmp->w/2, anchor->actuel->bmp->h, itofix(0));
                pivot_sprite(buffer,find_bitmap(anchor->actuel, anchor->img_nb)->bmp,anchor->x,anchor->y,0,15,itofix(anchor->angle));
            }
            else if(anchor->metier==3)
            {
              bmp= find_bitmap(anchor->actuel, anchor->img_nb);
            if(anchor->souffle->dx>0) pivot_sprite(buffer,bmp->bmp, anchor->x, anchor->y-anchor->actuel->bmp->h/2,(int)(anchor->actuel->bmp->w/2),anchor->actuel->bmp->h/2, itofix(anchor->angle));
                else pivot_sprite_v_flip(buffer,bmp->bmp, anchor->x, anchor->y-anchor->actuel->bmp->h/2,(int)(anchor->actuel->bmp->w/2),anchor->actuel->bmp->h/2, itofix( 128+anchor->angle));

            }
            else
            {
                bmp= find_bitmap(anchor->actuel, anchor->img_nb);

                /*if(anchor->dx>0 || anchor->jump==1)draw_sprite(buffer, bmp->bmp,anchor->x-bmp->bmp->w/2, anchor->y-bmp->bmp->h);
                else if(anchor->dx<0 || anchor->jump==-1) draw_sprite_h_flip(buffer, bmp->bmp,anchor->x-bmp->bmp->w/2, anchor->y-bmp->bmp->h);*/
                if(anchor->dx>0 || anchor->jump==1) pivot_sprite(buffer,bmp->bmp, anchor->x, anchor->y-anchor->actuel->bmp->h/2,(int)(anchor->actuel->bmp->w/2),anchor->actuel->bmp->h/2, itofix(anchor->angle));
                else if(anchor->dx<0 || anchor->jump==-1) pivot_sprite_v_flip(buffer,bmp->bmp, anchor->x, anchor->y-anchor->actuel->bmp->h/2,(int)(anchor->actuel->bmp->w/2),anchor->actuel->bmp->h/2, itofix( 128+anchor->angle));
            }


            if(anchor->selected)
            {
                //pivot_sprite(buffer, arrow,(7+anchor->x-anchor->actuel->bmp->h)*sin(angle), (7+anchor->y-anchor->actuel->bmp->h)*(cos(angle)), coord_x_bout, coord_y_bout, angle);
                pivot_sprite(buffer,barre_vie(anchor),anchor->x+(anchor->actuel->bmp->h)*sin(anchor->angle*2*M_PI/(255)),anchor->y-(anchor->actuel->bmp->h)*(cos(anchor->angle*2*M_PI/(255))), barre_vie(anchor)->w/2, barre_vie(anchor)->h, itofix(anchor->angle));

            }
        }
        anchor=anchor->next;
        //printf("display\n");
    }
}

void Move_players(t_chainB* basic,t_chainB* roach,t_chainB* souffle, t_ent *player_anchor, BITMAP* collision_map, t_chainB* jump_basic, BITMAP* front )
{
    int test=1;
    int height_x=SCREEN_H, height_y=SCREEN_H;


    switch(test_mur( player_anchor,  collision_map, &height_x, &height_y))
    {
    case 0:
        if(player_anchor->metier==1 && player_anchor->metier_on==1)
        {
            player_anchor->metier_on=0;
            player_anchor->metier=0;
            player_anchor->actuel=basic;
            player_anchor->img_nb=0;
            player_anchor->dx=PLAYER_SPEED;
        }
        player_anchor->angle=0;
        break;
    case 2:
        if(player_anchor->metier!=1)player_anchor->dx=-player_anchor->dx;
        else
        {
            if(!player_anchor->metier_on) player_anchor->metier_on=1;
            creuser(collision_map, player_anchor, front);
        }
        break;
    case 3:
        player_anchor->dx=-player_anchor->dx;
        break;
    case 1:
        if(player_anchor->dx) player_anchor->angle= (-player_anchor->dx/abs(player_anchor->dx))*atan2 (player_anchor->y-height_y,(player_anchor->x-height_x>0?player_anchor->x-height_x: height_x-player_anchor->x))*(255/(2*M_PI));
        //player_anchor->dy= player_anchor->dx*sin((player_anchor->angle/255)*360);
        printf("\n\n\n\n\n   HEIGHT Y %d  %d\n\n\n\n ", player_anchor->y-height_y, player_anchor->x-height_x) ;
        player_anchor->y+=(player_anchor->dx*(height_y-player_anchor->y))/(height_x-player_anchor->x)-1;

        break;
    }


    //system("pause");
    printf("\n\n%d  %d  %d\n\n\n\n",getpixel(collision_map,player_anchor->x, player_anchor->y-10),height_x, height_y);

    //if(distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC)<abs(player_anchor->dy+1) && player_anchor->jump)player_anchor->y+=(player_anchor->dx-abs(player_anchor->dx)? -1:1)*distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC)-player_anchor->dy;

    switch (getpixel(collision_map,player_anchor->x, player_anchor->y+1+player_anchor->dy))
    {
    case BLANC:
    case BLEU:
        if(player_anchor->jump)
        {
            if(player_anchor->metier!=2)player_anchor->dx= PLAYER_SPEED*player_anchor->jump;
            //player_anchor->y-=distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC);
            player_anchor->jump=0;
            player_anchor->y+=distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC);
            player_anchor->dy=0;
            if(player_anchor->fall_count-55>0) player_anchor->vie-=(player_anchor->fall_count-55);
            player_anchor->fall_count=0;

            player_anchor->angle=0;
        }
        break;
    }
    switch(getpixel(collision_map, player_anchor->x+(player_anchor->dx/(player_anchor->dx? abs(player_anchor->dx):1))*((player_anchor->actuel->bmp->w/2-10)*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-(sin(player_anchor->angle*2*M_PI/255)<0? sin(player_anchor->angle*2*M_PI/255):0) *(player_anchor->actuel->bmp->w/2+7)))
    {
    case 0:
    case ROUGE:
        printf("\n\n\n\n\n\n\n COUCOUCOUCOUCOUCOUCOUCOUCOCUOUCOUCO\n\n\n\n\n\n\n\n\n C'EST MOIIIIIIIIIIIIII\n\n\n\n\n");
        if(distance_y_to_color(player_anchor->x+(player_anchor->dx/(player_anchor->dx? abs(player_anchor->dx):1))*((player_anchor->actuel->bmp->w/2+2)*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLANC)>30)
        {
            if(distance_y_to_color(player_anchor->x+(player_anchor->dx/(player_anchor->dx? abs(player_anchor->dx):1))*((player_anchor->actuel->bmp->w/2+2)*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLEU)>30)
            {
                printf ("CASE 0\n\n\n\n\n\n");
                if(player_anchor->jump==0)
                {
                    player_anchor->jump=player_anchor->dx/abs(player_anchor->dx);
                    player_anchor->img_nb=0;
                    //player_anchor->actuel=jump_basic;
                    if(player_anchor->metier!=2)player_anchor->dx=15* (player_anchor->dx/abs(player_anchor->dx));
                    player_anchor->dy=-10;
                }
                if(player_anchor->metier!=2)if(player_anchor->dx>2  || player_anchor->dx<-2) player_anchor->dx+= (-1)*(player_anchor->dx/abs(player_anchor->dx));
                if(player_anchor->dy<20)player_anchor->dy++;
                player_anchor->img_nb=1;
                player_anchor->fall_count+=player_anchor->dy;
            }
            else /*if(distance_y_to_color(player_anchor->x+(player_anchor->dx/(abs(player_anchor->dx)? abs(player_anchor->dx) : 1))*player_anchor->actuel->bmp->w/2, player_anchor->y+1, collision_map, BLEU)<distance_y_to_color(player_anchor->x+(player_anchor->dx/(abs(player_anchor->dx)? abs(player_anchor->dx) : 1))*player_anchor->actuel->bmp->w/2, player_anchor->y+1, collision_map, BLANC))
         */
            {

                if(player_anchor->metier!=2 && !player_anchor->jump)player_anchor->angle=(255/(2*M_PI))*(player_anchor->dx-abs(player_anchor->dx)? -1:1)*atan2(distance_y_to_color(player_anchor->x+(player_anchor->dx/(player_anchor->dx? abs(player_anchor->dx): 1))*(player_anchor->actuel->bmp->w/2*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLEU), player_anchor->actuel->bmp->w/2+player_anchor->dx);
                player_anchor->y+=(distance_y_to_color(player_anchor->x-(player_anchor->dx-abs(player_anchor->dx)? -1:1)*(player_anchor->actuel->bmp->w/2*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLEU)<30 ? distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLEU): 30);

            }
            /*else
            {
                player_anchor->y+=(distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC)<10 ? distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC): 10);
            if(player_anchor->metier!=2)player_anchor->angle=(255/(2*M_PI))*(player_anchor->dx/abs(player_anchor->dx))*atan2(distance_y_to_color(player_anchor->x+(player_anchor->dx/abs(player_anchor->dx))*(player_anchor->actuel->bmp->w/2+10), player_anchor->y, collision_map, BLANC), player_anchor->actuel->bmp->w/2+player_anchor->dx);

            }*/
        }
        else /*if(distance_y_to_color(player_anchor->x+(player_anchor->dx/(abs(player_anchor->dx)? abs(player_anchor->dx) : 1))*player_anchor->actuel->bmp->w/2, player_anchor->y+1, collision_map, BLEU)>=distance_y_to_color(player_anchor->x+(player_anchor->dx/(abs(player_anchor->dx)? abs(player_anchor->dx) : 1))*player_anchor->actuel->bmp->w/2, player_anchor->y+1, collision_map, BLANC))
        {*/
        {

            if(player_anchor->metier!=2 && !player_anchor->jump)player_anchor->angle=(255/(2*M_PI))*(player_anchor->dx-abs(player_anchor->dx)? -1:1)*atan2(distance_y_to_color(player_anchor->x+(player_anchor->dx-abs(player_anchor->dx)? -1:1)*(player_anchor->actuel->bmp->w/2*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLANC), player_anchor->actuel->bmp->w/2+player_anchor->dx);
            player_anchor->y+=(distance_y_to_color(player_anchor->x-(player_anchor->dx/(player_anchor->dx? abs(player_anchor->dx):1))*(player_anchor->actuel->bmp->w/2*cos(player_anchor->angle*2*M_PI/255)), player_anchor->y-sin(player_anchor->angle*2*M_PI/255)*player_anchor->actuel->bmp->w/2, collision_map, BLANC)<30 ? distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLANC): 30);

        }
        /* else
         {
             player_anchor->y+=(distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, 0)<100 ? distance_y_to_color(player_anchor->x, player_anchor->y, collision_map, BLEU): 100);
             if(player_anchor->metier!=2)player_anchor->angle=(255/(2*M_PI))*(player_anchor->dx/abs(player_anchor->dx))*atan2(distance_y_to_color(player_anchor->x+(player_anchor->dx/abs(player_anchor->dx))*(player_anchor->actuel->bmp->w/2+10), player_anchor->y, collision_map, BLEU), player_anchor->actuel->bmp->w/2+player_anchor->dx);+
         }*/

        break;

    }
    switch(getpixel(collision_map, player_anchor->x, player_anchor->y-10))
    {
    case ROUGE:
        player_anchor->vie=0;
        break;
    }


    printf("\n\nANGLE %d\n\n", player_anchor->angle);
    player_anchor->x+=player_anchor->dx;
    if (player_anchor->x+player_anchor->actuel->bmp->w/2>=collision_map->w) player_anchor->dx*= (-1);
    else if (player_anchor->x-player_anchor->actuel->bmp->w/2<=0) player_anchor->dx*= (-1);
    player_anchor->y+=player_anchor->dy;
    if (player_anchor->y>=SCREEN_H)
    {
        player_anchor->dy= 0;
        player_anchor->y=SCREEN_H;
    }
    else if(player_anchor->y<=0)
    {
        player_anchor->y=0;
    }
    printf("%d", player_anchor->vie);
}

void Game_on(int lvl_nb, t_chainB* anchor,t_chainB* basic,t_chainB* jump_basic, t_chainB* roach, t_chainB* scroll, t_chainB* aiguille, t_chainB* souffle)
{
    printf("game_on\n");
    BITMAP* collision_map;
    BITMAP* buffer;
    BITMAP* page;
    BITMAP* fond_ecran=load_bitmap("Images/fond_ecran.bmp", NULL);
    BITMAP* front= load_bitmap("Images/front.bmp",NULL);
    BITMAP* scrolling_mouse= load_bitmap("Images/curseur.bmp", NULL);
    clear_bitmap(screen);
    int pos_blit_x=0;
    int pos_blit_y=0;
    int goal_x, goal_y;
    page=create_bitmap(SCREEN_W, SCREEN_H);
    t_ent* player_anchor=NULL;
    t_ent* buff;
    t_button buttons[NB_METIER];
    t_spike spike_anchor;
    clock_t first;
    lvl_nb=1;
    int game=1, players_nb=0, tot_play=0;
    int i=0;
    level_load(lvl_nb, &collision_map, &tot_play, &player_anchor, basic, &goal_x, &goal_y);
    buffer=create_bitmap(collision_map->w, collision_map->h);
    buff=player_anchor;
    first= clock() + 2* CLOCKS_PER_SEC;
    init_buttons(buttons, basic, roach, aiguille, souffle);
    while (game && !key[KEY_ESC])
    {
        scare_mouse();
        clear_bitmap(buffer);
        clear_bitmap(page);
        if((clock()>first)&&(players_nb<tot_play))
        {
            players_nb++;
            first= clock() + 2* CLOCKS_PER_SEC;
        }
        for(i=0; i<players_nb; i++)
        {
            if(buff->vie>0)
            {
                if(buff->appeared==0)
                {
                    buff->appeared=1;
                    buff->start_anim=clock()+0.1*CLOCKS_PER_SEC;
                    buff->start_mov=clock()+buff->image_refresh*CLOCKS_PER_SEC;
                }
                if(buff->start_anim<=clock())
                {
                    if(buff->metier!=3) Move_players(basic, roach, scroll,buff, collision_map, jump_basic, front);
                    buff->start_anim=clock()+0.1*CLOCKS_PER_SEC;
                }
                if(buff->start_mov<=clock())
                {
                    change_img(buff);
                    buff->start_mov=clock()+buff->image_refresh*CLOCKS_PER_SEC;
                }
                mouse_check(buff, player_anchor, pos_blit_x, pos_blit_y, collision_map, buttons);
            }
            buff=buff->next;
        }
        buff=player_anchor;
        i=0;
        scrolling(&pos_blit_x, &pos_blit_y, scroll, buffer, collision_map);
        blit(collision_map, buffer, 0,0,0,0, collision_map->w,collision_map->h);
        //blit(fond_ecran, page, 0,0,0,0, fond_ecran->w,fond_ecran->h);
        //masked_blit(front, buffer, 0,0,0,0, collision_map->w,collision_map->h);
        display_players(buff, buffer, collision_map, NULL, NULL, pos_blit_x, pos_blit_y);
        display_buttons(buttons, page);
        blit(buffer, page, pos_blit_x,pos_blit_y,0,0, SCREEN_W, SCREEN_H-150);
        show_mouse(page);
        blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    }

}
END_OF_FUNCTION();

t_chainB* find_bitmap(t_chainB* start, int step)
{
    int i;
    for(i=0; i<step; i++)
    {
        start=start->next;
    }
    return start;
}

void load_all_bitmap(t_chainB* anchor,t_chainB **basic_point,t_chainB **roach_point,t_chainB **scroll_point, t_chainB** aiguille_pos, t_chainB** souffle_pos)
{
    char mot[50];

    int i;
    for(i=0; i<NB_SPRITE; i++)
    {
        if (i<NB_SPRITE_ENVIRONNEMENT)
        {
            switch(i)
            {
            case 0:
                sprintf(mot, "Images/scroll_r.bmp");
                break;
            case 1:
                sprintf(mot, "Images/scroll_l.bmp");
                break;
            case 2:
                sprintf(mot, "Images/fond_menu.bmp");
                break;
            case 3:
                sprintf(mot, "Images/front.bmp");
                break;
            }
        }
        else if(i<NB_SPRITE_BASIC) sprintf(mot, "Images/basic%d.bmp", i-2);
        else if(i< NB_SPRITE_ROACH)
        {
            sprintf(mot, "Images/roach%d.bmp", i-NB_SPRITE_BASIC+1);
        }
        else if(i< NB_SPRITE_AIGUILLE) sprintf(mot, "Images/aiguillon%d.bmp", i-NB_SPRITE_ROACH);

        else if(i< NB_SPRITE_SOUFFLE)
        {
            sprintf(mot, "Images/mutalisk%d.bmp", i-NB_SPRITE_AIGUILLE);
            printf("%s", mot);
        }

        if(i==NB_SPRITE_BASIC) *roach_point= anchor;
        if(i==0) *scroll_point= anchor;
        if(i==2) *basic_point=anchor;
        if(i==NB_SPRITE_ROACH) *aiguille_pos=anchor;
        if(i==NB_SPRITE_AIGUILLE) *souffle_pos=anchor;
        anchor->bmp=load_bitmap(mot,NULL);
        clear(screen);

        if(i+1==NB_SPRITE)anchor->next=NULL;
        else
        {
            anchor->next= (t_chainB*) malloc(sizeof(t_chainB));
            anchor=anchor->next;
        }
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
            i=0;
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

int menu(t_chainB* anchor,t_chainB *basic,t_chainB *stairs,t_chainB *scroll, t_chainB* jump_basic, t_chainB* aiguille, t_chainB* souffle)
{
    BITMAP* fond_menu;
    BITMAP* buffer=create_bitmap(SCREEN_W, SCREEN_H);
    FILE* level_save;
    int lvl_nb=1;
    printf("%d", makecol(0,255,0));
    fond_menu= load_bitmap("Images/fond_menu.bmp",NULL);
    char input[50];
    level_save=fopen("TXT/level_save.txt", "r");
    fscanf(level_save,"%d", &lvl_nb);
    lvl_nb=1;
    blit(fond_menu, buffer, 0,0,0,0, SCREEN_W, fond_menu->h);
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    allegro_scan_string(input,768, 192, makecol(255,0,255), makecol(255,255,255), "Quel est votre choix?", font);

    if(!strcmp(input, "jouer"))
    {
        Game_on(lvl_nb, anchor, basic,jump_basic, stairs, scroll, aiguille, souffle);
    }

    destroy_bitmap(fond_menu);
    destroy_bitmap(buffer);
    return 0;
}
END_OF_FUNCTION();
int main()
{
    //if(allegro_demarre()) printf("ooops\n");
    allegro_init();
    install_keyboard();
    install_mouse();
    BITMAP* lolus=load_bitmap("Image/curseur.bmp", NULL);
    set_mouse_sprite(lolus);
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000,700,0,0);
    t_chainB* waypt[NB_CAT];
    t_chainB anchor;
    load_all_bitmap(&anchor, &(waypt[BASIC_POS]), &(waypt[STAIRS_POS]), &(waypt[SCROLL_POS]), &waypt[AIGUILLE_POS], &waypt[SOUFFLE_POS]);
    while(menu(&anchor, waypt[BASIC_POS], waypt[STAIRS_POS], waypt[SOUFFLE_POS], waypt[JUMP_POS], waypt[AIGUILLE_POS], waypt[SOUFFLE_POS]));
    return 0;
}
END_OF_MAIN();
