#include "file.h"

void menu()
{
    //Déclaration des variables
    int nbPlayers=-1;
    int l=0;
    t_library *library=(t_library*)malloc(sizeof(t_library));
    if(!library)
        puts("!!! Probleme d'allocation !!!");
    t_queue* actual;
    t_queue* queue_=(t_queue*)malloc(sizeof(t_queue));
    if(!queue_)
        puts("!!! Probleme d'allocation !!!");
    t_character** characters=(t_character**)malloc(CHARACTER*sizeof(t_character*));
    for(int i=0; i<CHARACTER; i++)
    {
        characters[i]=(t_character*)malloc(sizeof(t_character));
        if(!characters[i])
            puts("!!! Probleme d'allocation !!!");
    }
    t_cell*** grid=(t_cell***)malloc(14*sizeof(t_cell**));
    for(int i=0; i<14; i++)
    {
        grid[i]=malloc(24*sizeof(t_cell*));
        if(!grid[i])
            puts("!!! Probleme d'allocation !!!");
        for(int j=0; j<24; j++)
        {
            grid[i][j]=(t_cell*)malloc(sizeof(t_cell));
            if(!grid[i][j])
                puts("!!! Probleme d'allocation !!!");
        }
    }

    clock_t prevTime=clock(), actualTime=clock();
    t_player** players;
    //Initialisation
    srand(time(NULL));
    init_alleg();
    initialization_map(&grid,dynamic_char("plain"));
    initialization_character(&characters);
    initialization_library(&library,&characters);

    //Boucle du menu principal
    do
    {
        if((actualTime-prevTime)/(CLOCKS_PER_SEC/1000)>DURATION)    //Toutes les DURATION ms
        {
            blit(library->l_MenuBackground,library->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            if(mouse_x>SCREEN_W/2-library->l_MenuLaunchButton[1]->w/2 && mouse_x<SCREEN_W/2+library->l_MenuLaunchButton[1]->w/2 && mouse_y>SCREEN_H/3-library->l_MenuLaunchButton[1]->h/2 && mouse_y<SCREEN_H/3+library->l_MenuLaunchButton[1]->h/2)
            {
                if(mouse_b&1)       //Si clic sur bouton
                {
                    while(mouse_b&1);
                    nbPlayers=menu_nb_players(&library);        //Choix nombre de joueurs
                    players=(t_player**)malloc(nbPlayers*sizeof(t_player*));
                    if(!players)
                        puts("!!! Probleme d'allocation !!!");
                    initialization_player(&library,&characters,nbPlayers,&queue_);      //Constitution de la file de jeu + choix pseudo et classe
                    actual=queue_;
                    do{
                        players[l]=actual->data;
                        initialise_position(grid,actual->data);
                        actual=actual->next;
                        l++;
                    }while((actual));
                    //queue_display(&queue_);
                    display_map(&library,&grid, players, nbPlayers);
                    break;
                }
                masked_blit(library->l_MenuLaunchButton[1],library->l_Buffer,0,0,SCREEN_W/2-library->l_MenuLaunchButton[1]->w/2,SCREEN_H/3-library->l_MenuLaunchButton[1]->h/2,SCREEN_W,SCREEN_H);
            }
            else
                masked_blit(library->l_MenuLaunchButton[0],library->l_Buffer,0,0,SCREEN_W/2-library->l_MenuLaunchButton[1]->w/2,SCREEN_H/3-library->l_MenuLaunchButton[1]->h/2,SCREEN_W,SCREEN_H);
            blit(library->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        actualTime=clock();
    }while(!key[KEY_ESC]);

    //Libération mémoire
    destroy_library(&library);
    free(library);
    free(queue_);
    //queue_empty(&queue_);
    for(int i=0; i<CHARACTER; i++)
    {
        for(int j=0; j<4; j++)
            free(characters[i]->c_spell[j]);
        free(characters[i]);
    }
    for(int i=0; i<14; i++)
    {
        for(int j=0; j<24; j++)
            free(grid[i][j]);
        free(grid[i]);
    }
}

int menu_nb_players(t_library** library)        //SSP choix nombre de joueurs
{
    //Déclaration des variables
    int nbPlayers=-1, i=0;
    clock_t prevTime=clock(), actualTime=clock();

    //Boucle du choix
    do
    {
        if((actualTime-prevTime)/(CLOCKS_PER_SEC/1000)>DURATION)    //Toutes les DURATION ms
        {
            blit((*library)->l_MenuBackground,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit((*library)->l_MenuNbTitle,(*library)->l_Buffer,0,0,SCREEN_W/2-(*library)->l_MenuNbTitle->w/2,SCREEN_H/3-(*library)->l_MenuNbTitle->h/2,SCREEN_W,SCREEN_H);
            for(i=0; i<3; i++)
            {
                if(mouse_x>SCREEN_W/6*(i+2)-(*library)->l_MenuNbButton[i][1]->w/2 && mouse_x<SCREEN_W/6*(i+2)+(*library)->l_MenuNbButton[i][1]->w/2 && mouse_y>SCREEN_H/2-(*library)->l_MenuNbButton[i][1]->h/2 && mouse_y<SCREEN_H/2+(*library)->l_MenuNbButton[i][1]->h/2)
                {
                    if(mouse_b&1)       //Si clic sur bouton
                    {
                        nbPlayers=i+2;
                        while(mouse_b&1);
                        return nbPlayers;
                    }
                    masked_blit((*library)->l_MenuNbButton[i][1],(*library)->l_Buffer,0,0,SCREEN_W/6*(i+2)-(*library)->l_MenuNbButton[i][1]->w/2,SCREEN_H/2-(*library)->l_MenuNbButton[i][1]->h/2,SCREEN_W,SCREEN_H);
                }
                else
                    masked_blit((*library)->l_MenuNbButton[i][0],(*library)->l_Buffer,0,0,SCREEN_W/6*(i+2)-(*library)->l_MenuNbButton[i][1]->w/2,SCREEN_H/2-(*library)->l_MenuNbButton[i][1]->h/2,SCREEN_W,SCREEN_H);
            }
            blit((*library)->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        actualTime=clock();
    }while(!key[KEY_ESC]);

    return nbPlayers;
}

void initialise_position(t_cell*** grid, t_player* player){
    int column;
    int row;
    do{
        column=rand()%24;
        row=rand()%14;
    }while(grid[row][column]->cl_availability>0);
    player->p_ColumnPos=column;
    player->p_RowPos=row;
}
