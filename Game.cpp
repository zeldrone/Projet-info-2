

void init_player(t_ent* player, int input2, int input3, int basic)
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
}
int Move_players(t_chainB* basic,t_chainB* stairs,t_chainB* souffle, t_ent *player_anchor, BITMAP* collision_map, t_chainB* jump_basic )
{
    while(player_anchor)
    {
        player_anchor->x+=player_anchor->dx;
        player_anchor->y+=player_anchor->dy;

        switch (getpixel(collision_map,player_anchor->x, player_anchor->y))
        {
        case BLANC:
            player_anchor->dx= PLAYER_SPEED*((player_anchor->dx/(abs(player_anchor->dx) ? player_anchor->dx: 1)) ? player_anchor->dx/abs(player_anchor->dx) : 1) ;
            break;
        case 0:
            if(player_anchor->jump==0)
            {
                player_anchor->jump=1;
                player_anchor->img_nb=0;
                player_anchor->actuel=jump_basic->bmp;
                player_anchor->dx=5;
                player_anchor->dy=-10;
            }
            player_anchor->dx--;
            player_anchor->dy++;
            break;
        case ROUGE:
            player_anchor->vie=0;
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
    first=time(NULL);
    while (game)
    {
        test=time(NULL);
        if(players_nb<tot_play)players_nb=difftime(test, first)/5;
        buff.actuel=anchor->bmp;
        for(i=0; i<players_nb; i++)
        {
            Move_players(basic, stairs, souffle,&player_anchor, collision_map, jump_basic );
        }
        //if(difftime(test,first)%2) for(i=0; i<nb_spikes)

    }

}END_OF_FUNCTION();
