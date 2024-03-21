#include "file.h"

int menu()
{
    //Déclaration des variables
    int nbPlayers=-1, l=0, choix=0;
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
    initialization_map(&grid,dynamic_char("plain"));
    initialization_character(&characters);
    initialization_library(&library,&characters);

    //Lancement musique menu
    play_sample(library->l_Intro,127,128,1000,1);

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
                    choix=0;
                    nbPlayers=menu_nb_players(&library);        //Choix nombre de joueurs
                    players=(t_player**)malloc(nbPlayers*sizeof(t_player*));
                    if(!players)
                        puts("!!! Probleme d'allocation !!!");
                    initialization_player(&library,&characters,nbPlayers,&queue_);      //Constitution de la file de jeu + choix pseudo et classe
                    stop_sample(library->l_Intro);      //Arret musique
                    do{
                        actual=queue_;
                        do{
                            actual->data->p_alive=1;
                            actual->data->p_PV=characters[actual->data->p_character]->c_PV;
                            actual->data->p_PM=characters[actual->data->p_character]->c_PM;
                            actual->data->p_PA=characters[actual->data->p_character]->c_PA;
                            players[l]=actual->data;
                            players[l]->p_frame=0;
                            initialise_position(grid,actual->data);
                            actual=actual->next;
                            l++;
                        }while((actual));
                        while(key[KEY_ESC]);
                        choix=display_map(&library,&grid, players, nbPlayers, characters);        //Appel boucle de jeu
                    }while(choix==1);
                    break;
                }
                masked_blit(library->l_MenuLaunchButton[1],library->l_Buffer,0,0,SCREEN_W/2-library->l_MenuLaunchButton[1]->w/2,SCREEN_H/3-library->l_MenuLaunchButton[1]->h/2,SCREEN_W,SCREEN_H);
            }
            else
                masked_blit(library->l_MenuLaunchButton[0],library->l_Buffer,0,0,SCREEN_W/2-library->l_MenuLaunchButton[1]->w/2,SCREEN_H/3-library->l_MenuLaunchButton[1]->h/2,SCREEN_W,SCREEN_H);
            blit(library->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        actualTime=clock();
    }while(!key[KEY_ESC] && choix!=2);
    //Libération mémoire
    destroy_library(&library);
    free(library);
    free(queue_);
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
    return(choix);
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

void initialise_position(t_cell*** grid, t_player* player)      //SSP d'apparition aléatoire du joueur sur la map
{
    int column;
    int row;
    do{
        column=rand()%24;       //Colonne aléatoire
        row=rand()%14;      //Ligne aléatoire
    }while(grid[row][column]->cl_availability>0 || row<1 || column<2);      //Blindage pour ne pas apparaitre sur un obstracle
    player->p_ColumnPos=column;     //Attribution des nouvelles coordonnées
    player->p_RowPos=row;
}
