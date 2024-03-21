#include "file.h"

void init_alleg()       //SSP initialisation allegro
{
    allegro_init();                     //Initialisation allegro
    set_color_depth(desktop_color_depth());             //Sélection de la profondeur de couleur
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,700,0,0))              //Définir un mode graphique
    {
        //Contrôler si le mode graphique fonctionne
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    install_keyboard();             //Pour disposer du clavier(si besoin)
    install_mouse();                //Pour disposer de la souris(si besoin)
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    show_mouse(screen);
}

char* dynamic_char(char string[TAILLE_MAX])        //Création de chaîne dyna rapide
{
    char* stringLink=NULL;
    stringLink=realloc(stringLink,(strlen(string)+1)*sizeof(char));
    if(!stringLink)
        puts("!!! Probleme d'allocation !!!");
    strcpy(stringLink,string);
    return stringLink;
}

void initialization_library(t_library **library, t_character*** characters)     //Intialisation des BITMAPS/SAMPLE
{
    char buffer[100];
    (*library)->l_Buffer=create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap((*library)->l_Buffer);
    (*library)->l_Buffer2=create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap((*library)->l_Buffer2);

    (*library)->l_MenuBackground=load_bitmap_check("visual/menu/background.bmp");

    for(int i=0; i<6;i++)
    {
        sprintf(buffer,"visual/menu/launchbutton%d.bmp",i);
        (*library)->l_MenuLaunchButton[i]=load_bitmap_check(buffer);
    }

    (*library)->l_MenuNbTitle=load_bitmap_check("visual/menu/nbtitle.bmp");

    for(int i=0; i<3;i++)
    {
        sprintf(buffer,"visual/menu/nbbutton%doff.bmp",i+2);
        (*library)->l_MenuNbButton[i][0]=load_bitmap_check(buffer);
        sprintf(buffer,"visual/menu/nbbutton%don.bmp",i+2);
        (*library)->l_MenuNbButton[i][1]=load_bitmap_check(buffer);
    }

    (*library)->l_MenuPlayerTitle=load_bitmap_check("visual/menu/playertitle.bmp");

    for(int i=0; i<2;i++)
    {
        sprintf(buffer,"visual/menu/nextbutton%d.bmp",i);
        (*library)->l_Next[i]=load_bitmap_check(buffer);
    }

    for(int i=0; i<CHARACTER; i++)
    {
        sprintf(buffer,"visual/chararacter/%s/card.bmp",(*characters)[i]->c_name);
        (*library)->l_MenuCharacters[i]=load_bitmap_check(buffer);

        sprintf(buffer,"visual/chararacter/%s/static.bmp",(*characters)[i]->c_name);
        (*library)->l_Static[i]=load_bitmap_check(buffer);

        sprintf(buffer,"visual/chararacter/%s/ko.bmp",(*characters)[i]->c_name);
        (*library)->l_Ko[i]=load_bitmap_check(buffer);

        sprintf(buffer,"visual/chararacter/%s/walk.bmp",(*characters)[i]->c_name);
        (*library)->l_Walk[i]=load_bitmap_check(buffer);

        sprintf(buffer,"visual/chararacter/%s/melee.bmp",(*characters)[i]->c_name);
        (*library)->l_Melee[i]=load_bitmap_check(buffer);

        sprintf(buffer,"visual/chararacter/%s/control.bmp",(*characters)[i]->c_name);
        (*library)->l_Control[i]=load_bitmap_check(buffer);

        for(int j=0; j<4; j++)
        {
            sprintf(buffer,"visual/chararacter/%s/spell%d.bmp",(*characters)[i]->c_name,j);
            (*library)->l_Spell[i][j]=load_bitmap_check(buffer);
        }
    }

    (*library)->l_Plain=load_bitmap_check("visual/map/plain/plain.bmp");
    (*library)->l_PlainInfo=(t_mapinfo**)malloc(ELEMENT*sizeof(t_mapinfo*));
    for(int i=0; i<ELEMENT; i++)
    {
        (*library)->l_PlainInfo[i]=(t_mapinfo*)malloc(sizeof(t_mapinfo));
        if(!(*library)->l_PlainInfo[i])
            puts("!!! Probleme d'allocation !!!");
    }
    (*library)->l_PlainInfo[0]->mp_name=2;
    (*library)->l_PlainInfo[0]->mp_info=load_bitmap_check("visual/map/plain/2.bmp");
    (*library)->l_PlainInfo[1]->mp_name=-2;
    (*library)->l_PlainInfo[1]->mp_info=load_bitmap_check("visual/map/plain/-2.bmp");
    (*library)->l_PlainInfo[2]->mp_name=3;
    (*library)->l_PlainInfo[2]->mp_info=load_bitmap_check("visual/map/plain/3.bmp");
    (*library)->l_PlainInfo[3]->mp_name=-3;
    (*library)->l_PlainInfo[3]->mp_info=load_bitmap_check("visual/map/plain/-3.bmp");
    (*library)->l_PlainInfo[4]->mp_name=4;
    (*library)->l_PlainInfo[4]->mp_info=load_bitmap_check("visual/map/plain/4.bmp");
    (*library)->l_PlainInfo[5]->mp_name=-4;
    (*library)->l_PlainInfo[5]->mp_info=load_bitmap_check("visual/map/plain/-4.bmp");
    (*library)->l_PlainInfo[6]->mp_name=-5;
    (*library)->l_PlainInfo[6]->mp_info=load_bitmap_check("visual/map/plain/-5.bmp");
    (*library)->l_PlainInfo[7]->mp_name=-6;
    (*library)->l_PlainInfo[7]->mp_info=load_bitmap_check("visual/map/plain/-6.bmp");
    (*library)->l_PlainInfo[8]->mp_name=-7;
    (*library)->l_PlainInfo[8]->mp_info=load_bitmap_check("visual/map/plain/-7.bmp");

    (*library)->l_Intro=load_sample_check("audio/menu.wav");
    (*library)->l_Game=load_sample_check("audio/game.wav");
}

BITMAP *load_bitmap_check(char *imageName)       //Vérification qu'on trouve la BITMAP
{
    BITMAP *buffer;
    buffer=load_bitmap(imageName,NULL);
    if(!buffer)
    {
        allegro_message("pas pu trouver %s",imageName);
        exit(EXIT_FAILURE);
    }
    return buffer;
}

SAMPLE* load_sample_check(char *sampleName)      //Vérification qu'on trouve le SAMPLE
{
    SAMPLE* buffer;
    buffer=load_sample(sampleName);
    if(!buffer)
    {
        allegro_message("pas pu trouver %s",sampleName);
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void destroy_library(t_library **library)       //Destruction des BITMAP
{
    destroy_bitmap((*library)->l_Buffer);
    destroy_bitmap((*library)->l_Buffer2);
    destroy_bitmap((*library)->l_MenuBackground);

    for(int i=0; i<6;i++)
        destroy_bitmap((*library)->l_MenuLaunchButton[i]);

    destroy_bitmap((*library)->l_MenuNbTitle);

    for(int i=0; i<3;i++)
    {
        destroy_bitmap((*library)->l_MenuNbButton[i][0]);
        destroy_bitmap((*library)->l_MenuNbButton[i][1]);
    }

    destroy_bitmap((*library)->l_MenuPlayerTitle);

    for(int i=0; i<2;i++)
        destroy_bitmap((*library)->l_Next[i]);

    for(int i=0; i<CHARACTER; i++)
    {
        destroy_bitmap((*library)->l_MenuCharacters[i]);

        destroy_bitmap((*library)->l_Static[i]);

        destroy_bitmap((*library)->l_Ko[i]);

        destroy_bitmap((*library)->l_Walk[i]);

        destroy_bitmap((*library)->l_Melee[i]);

        destroy_bitmap((*library)->l_Control[i]);

        for(int j=0; j<4; j++)
            destroy_bitmap((*library)->l_Spell[i][j]);
    }

    destroy_bitmap((*library)->l_Plain);
    for(int i=0; i<ELEMENT; i++)
        destroy_bitmap((*library)->l_PlainInfo[i]->mp_info);
    for(int i=0; i<CHARACTER; i++)
        free((*library)->l_PlainInfo[i]);
}

void initialization_character(t_character*** characters)        //SSP d'initialisation des différentes classes depuis fichiers
{
    for(int i=0; i<CHARACTER; i++)
    {
        char string[TAILLE_MAX]="";
        sprintf(string,"config/character/character%d.txt",i);
        FILE* file=fopen(string,"r");
        if(file)        //Test si ouverture réussie
        {
            if(fgets(string,TAILLE_MAX,file))
            {
                string[strlen(string)-1]='\0';      //Retirer le \n de fin
                (*characters)[i]->c_name=dynamic_char(string);      //Passage en char*
            }
            if(fgets(string,TAILLE_MAX,file))
            {
                string[strlen(string)-1]='\0';
                (*characters)[i]->c_PV=atoi(string);
            }
            if(fgets(string,TAILLE_MAX,file))
            {
                string[strlen(string)-1]='\0';
                (*characters)[i]->c_PM=atoi(string);
            }
            if(fgets(string,TAILLE_MAX,file))
            {
                string[strlen(string)-1]='\0';
                (*characters)[i]->c_PA=atoi(string);
            }
            for(int j=0; j<4; j++)
            {
                (*characters)[i]->c_spell[j]=(t_spell*)malloc(sizeof(t_spell));
                if(!(*characters)[i]->c_spell[j])
                    puts("!!! Probleme d'allocation !!!");
                if(fgets(string, TAILLE_MAX, file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_name=dynamic_char(string);
                }
                if(fgets(string,TAILLE_MAX,file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_RangeMin=atoi(string);
                }
                if(fgets(string,TAILLE_MAX,file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_RangeMax=atoi(string);
                }
                if(fgets(string,TAILLE_MAX,file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_type=atoi(string);
                }
                if(fgets(string,TAILLE_MAX,file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_damage=atoi(string);
                }
                if(fgets(string,TAILLE_MAX,file))
                {
                    string[strlen(string)-1]='\0';
                    (*characters)[i]->c_spell[j]->s_success=atoi(string);
                }
            }
            fclose(file);       //Fermeture du fichier après utilisation
        }
    }
}

void queue_enqueue(t_queue** queue_, t_player* data)       //SSP pour enfiler un joueur
{
    t_queue* new_=malloc(sizeof(t_queue));
    if(new_)
    {
        new_->next=NULL;
        new_->data=data;
        if(!(*queue_)->data)
            *queue_=new_;
        else
        {
            t_queue *p_tmp=*queue_;
            while(p_tmp->next)
                p_tmp=p_tmp->next;
            p_tmp->next=new_;
        }
    }
}

t_player* queue_dequeue(t_queue** queue_)       //SSP pour défiler un joueur
{
    t_player* del=(t_player*)malloc(sizeof(t_player));
    if(!del)
        puts("!!! Probleme d'allocation !!!");
    if(*queue_)
    {
        t_queue* tmp=(*queue_)->next;
        del=(*queue_)->data;
        free(*queue_);
        *queue_=NULL;
        *queue_=tmp;
    }
    return del;
}

char* random_pseudo()       //SSP de pseudo aléatoire
{
    char string[100]="";
    char* list[20];
    int i=0;
    FILE* file=fopen("config/nickname/nickname.txt","r");
    if(file)
    {
        while(fgets(string,TAILLE_MAX,file))
        {
            string[strlen(string)-1]='\0';      //Retrait du \n de fin de chaine
            list[i]=dynamic_char(string);       //Passage en char*
            i++;
            if(i>=20) break;        //Si plus grand que le tableau on arrete
        }
        fclose(file);       //Fermeture du fichier après utilisation

    }
    return list[rand()%i];
}

void initialization_player(t_library** library,t_character*** characters,int nbPlayers, t_queue** queue_)       //SSP de création de la file de joueurs et de remplissage de leurs informations
{
    //Définition des variables
    t_queue* queue_buffer=(t_queue*)malloc(sizeof(t_queue));
    if(!queue_buffer)
        puts("!!! Probleme d'allocation !!!");
    queue_buffer->data=NULL;
    queue_buffer->next=NULL;

    clock_t prevTime=clock(), actualTime=clock();

    //Boucle de complétion des infos joueurs
    for(int i=0; i<nbPlayers; i++)
    {
        //Définition de variables temporaires
        char touch;
        char string_pseudo[20+1]="";
        char buffer[10]="";
        int end=0,j=0;
        //Boucle allegro
        do{
            if((actualTime-prevTime)/(CLOCKS_PER_SEC/1000)>DURATION)    //Toutes les DURATION ms
            {
                blit((*library)->l_MenuBackground,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                masked_blit((*library)->l_MenuPlayerTitle,(*library)->l_Buffer,0,0,SCREEN_W/2-(*library)->l_MenuPlayerTitle->w/2,SCREEN_H/5-(*library)->l_MenuPlayerTitle->h/2,SCREEN_W,SCREEN_H);
                for(int k=0; k<CHARACTER; k++)
                {
                    //Affichage infos des classes
                    masked_blit((*library)->l_MenuCharacters[k],(*library)->l_Buffer,0,0,SCREEN_W/2-(*library)->l_MenuCharacters[k]->w*2+(*library)->l_MenuCharacters[k]->w*k,SCREEN_H/4,SCREEN_W,SCREEN_H);
                    sprintf(buffer,"%d",(*characters)[k]->c_PV);
                    textprintf_ex((*library)->l_Buffer,font,SCREEN_W/4+35+(*library)->l_MenuCharacters[k]->w*k,SCREEN_H/4+18,makecol(255,255,255),-1,buffer);
                    sprintf(buffer,"%d",(*characters)[k]->c_PM);
                    textprintf_ex((*library)->l_Buffer,font,SCREEN_W/5+25+(*library)->l_MenuCharacters[k]->w*k,SCREEN_H/2+3,makecol(255,255,255),-1,buffer);
                    sprintf(buffer,"%d",(*characters)[k]->c_PA);
                    textprintf_ex((*library)->l_Buffer,font,SCREEN_W/5+25+(*library)->l_MenuCharacters[k]->w*k,SCREEN_H/2+39,makecol(255,255,255),-1,buffer);
                    if((mouse_b&1) && mouse_x>SCREEN_W/2-(*library)->l_MenuCharacters[k]->w*2+(*library)->l_MenuCharacters[k]->w*k && mouse_x<SCREEN_W/2-(*library)->l_MenuCharacters[k]->w*2+(*library)->l_MenuCharacters[k]->w*k+(*library)->l_MenuCharacters[k]->w && mouse_y>SCREEN_H/4 && mouse_y<SCREEN_H/4+(*library)->l_MenuCharacters[k]->h)
                    {
                        queue_enqueue(&queue_buffer,dyna_player(0,0,(*characters)[k]->c_PV,(*characters)[k]->c_PM,(*characters)[k]->c_PA,k,1,j, string_pseudo));
                        while(mouse_b&1);
                        end=1;
                    }
                }
                if(keypressed())       //Gestion saisie
                {
                    touch=readkey();
                    if(touch==8 && j>0)
                    {
                        string_pseudo[j-1]='\0';
                        j--;
                    }
                    else if(j<20 && touch>=33 && touch<=125)
                    {
                        string_pseudo[j]=touch;
                        j++;
                    }
                }
                rectfill((*library)->l_Buffer,SCREEN_W/3,SCREEN_H/10*7-5,SCREEN_W*2/3,SCREEN_H/10*7+12,makecol(0,0,0));     //Affichage
                rectfill((*library)->l_Buffer,SCREEN_W/3+2,SCREEN_H/10*7-5+2,SCREEN_W*2/3-2,SCREEN_H/10*7+12-2,makecol(255,255,255));
                if(j==0) textprintf_ex((*library)->l_Buffer,font,SCREEN_W/2-strlen("Entrez votre pseudo")*4,SCREEN_H/10*7,makecol(0,0,0),makecol(255,255,255),"Entrez votre pseudo");       //Si vide afficher titre
                else textprintf_ex((*library)->l_Buffer,font,SCREEN_W/2-strlen(string_pseudo)*4,SCREEN_H/10*7,makecol(0,0,0),makecol(255,255,255),"%s",string_pseudo);      //Sinon afficher texte
                blit((*library)->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            actualTime=clock();
        }while(end==0);
    }
    **queue_=*queue_buffer;

    //Libération de la mémoire
    free(queue_buffer);
}

t_player* dyna_player(int rowpos, int columnpos, int PV, int PM, int PA, int character, int alive, int j, char* string_pseudo)      //SSP d'allocation dynamique d'un joueur
{
    t_player* actual=(t_player*)malloc(sizeof(t_player));
    if(!actual)
        puts("!!! Probleme d'allocation !!!");      //Blindage
    if(j>2) actual->p_name=dynamic_char(string_pseudo);     //Si pseudo non renseigné choix depuis un fichier de pseudo
    else actual->p_name=random_pseudo();
    actual->p_RowPos=rowpos;        //Affectation des attributs
    actual->p_ColumnPos=columnpos;
    actual->p_PV=PV;
    actual->p_PM=PM;
    actual->p_PA=PA;
    actual->p_character=character;
    actual->p_alive=alive;
    return actual;
}

void queue_display(t_queue** queue_)        //SSP Debug
{
    t_player *current=(t_player*)malloc(sizeof(t_player));
    if(!current)
        puts("!!! Probleme d'allocation !!!");
    t_queue* queue_buffer=(t_queue*)malloc(sizeof(t_queue));
    if(!queue_buffer)
        puts("!!! Probleme d'allocation !!!");
    *queue_buffer=**queue_;

    while(queue_buffer)
    {
        current=queue_dequeue(&queue_buffer);
        printf("\nJoueur :\n");
        if(!current)
            puts("vide");
        printf("Nom: %s\n",current->p_name);
        printf("Classe: %d\n",current->p_character);
        printf("PV: %d\n",current->p_PV);
        printf("PM: %d\n",current->p_PM);
        printf("PA: %d\n",current->p_PA);
        printf("Position colonne: %d\n",current->p_ColumnPos);
        printf("Position rang: %d\n",current->p_RowPos);
        printf("Vivant: %d\n",current->p_alive);
    }
    free(current);
    free(queue_buffer);
}

void queue_empty(t_queue** queue_)      //SSP pour vider une queue
{
    while(*queue_)
        free(queue_dequeue(queue_));
    free(*queue_);
}

int display_map(t_library** library,t_cell**** grid, t_player** players, int nbPlayers, t_character** characters)      //SSP de la boucle de jeu
{
    //Déclaration des variables
    clock_t prevTime=clock(), actualTime=clock(), currentTime=clock();
    int nbtours=0, spell_buffer=-1, moving=0, spell=0, ko=0, joueur_ko[nbPlayers], deadPlayers=0, choix=2, ko_buffer=0;;
    t_pair pair_, target, actual;
    t_player* ranking[nbPlayers];
    for(int i=0;i<nbPlayers;i++){
        joueur_ko[i]=-1;
    }

    play_sample((*library)->l_Game,127,128,1000,1);

    //Boucle d'affichage
    do
    {
        if((actualTime-prevTime)/(CLOCKS_PER_SEC/1000)>DURATION)    //Toutes les DURATION ms
        {
            blit((*library)->l_Plain,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            //for(int i=0;i<24;i++) vline((*library)->l_Buffer,i*50,0,SCREEN_H,makecol(255,255,255));       //Si l'on souhaite afficher une grille de fond
            //for(int i=0;i<14;i++) hline((*library)->l_Buffer,0,i*50,SCREEN_W,makecol(255,255,255));
            for(int i=0; i<14; i++)     //Affichage des obstacles sur la map
            {
                for(int j=0; j<24; j++)
                {
                    if((*grid)[i][j]->cl_availability<=-2 || (*grid)[i][j]->cl_availability>=2)
                    {
                        if((*grid)[i][j]->cl_availability==2)
                            masked_blit(find_element(library,(*grid)[i][j]->cl_availability),(*library)->l_Buffer,0,0,50*j-15,50*i-15,SCREEN_W,SCREEN_H);
                        else
                            masked_blit(find_element(library,(*grid)[i][j]->cl_availability),(*library)->l_Buffer,0,0,50*j,50*i,SCREEN_W,SCREEN_H);
                    }
                }
            }       //Affichage de la barre de controle
            bottom_display(library,players,characters,nbtours%nbPlayers);
            player_display(library,players,characters,nbPlayers,nbtours%nbPlayers);
            textprintf_ex((*library)->l_Buffer,font,SCREEN_W-(*library)->l_Next[1]->w-strlen(players[(nbtours+1)%nbPlayers]->p_name)*8,SCREEN_H-(*library)->l_Next[1]->h/2-3,makecol(0,0,0),-1,"%s",players[(nbtours+1)%nbPlayers]->p_name);
            for(int k=0;k<nbPlayers;k++){      //Affichage des joueurs sur la map
                if(k!=(nbtours%nbPlayers)){
                    if(players[k]->p_alive==1){
                        masked_blit((*library)->l_Static[players[k]->p_character],(*library)->l_Buffer,0,0,(players[k]->p_ColumnPos)*50+3,50*(players[k]->p_RowPos+1)-(*library)->l_Static[players[k]->p_character]->h,45,SCREEN_H);
                    }
                }
                else {
                    if(moving==0 && spell==0){
                        if(players[k]->p_alive==1){
                            color_path(players[k]->p_RowPos,players[k]->p_ColumnPos,(*library)->l_Buffer,4);
                            masked_blit((*library)->l_Static[players[k]->p_character],(*library)->l_Buffer,0,0,(players[k]->p_ColumnPos)*50+3,50*(players[k]->p_RowPos+1)-(*library)->l_Static[players[k]->p_character]->h,45,SCREEN_H);
                        }
                    }
                }
            }
            on_top_display(library,grid,players,nbPlayers,1);
            pair_=get_cell(mouse_x,mouse_y);        //Récupérer case de la souris
            if(ko==1){
                ko=0;
                for(int i=0;i<nbPlayers;i++){
                    if(joueur_ko[i]!=-1){
                        actual.first=players[joueur_ko[i]]->p_RowPos;
                        actual.second=players[joueur_ko[i]]->p_ColumnPos;
                        sprite_display(library,grid,players,nbPlayers,(*library)->l_Ko[players[joueur_ko[i]]->p_character],actual,1,300,1);
                        ranking[deadPlayers]=players[joueur_ko[i]];
                        joueur_ko[i]=-1;
                        deadPlayers++;
                    }
                }
            }
            if(spell==1){
                players[nbtours%nbPlayers]->p_PA-=1;
                if(spell_buffer!=-2){
                    actual.first=players[nbtours%nbPlayers]->p_RowPos;
                    actual.second=players[nbtours%nbPlayers]->p_ColumnPos;
                    sprite_display(library,grid,players,nbPlayers,(*library)->l_Spell[players[nbtours%nbPlayers]->p_character][spell_buffer],actual,2,150,1);
                    spell=0;
                    if(characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_type!=0 && characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_type!=2){
                        for(int f=0;f<nbPlayers;f++){
                            if(players[f]->p_RowPos==target.first && players[f]->p_ColumnPos==target.second && players[f]->p_alive){
                                if(((rand()%100)+1)<=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_success){
                                    players[f]->p_PV-=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_damage;
                                    if(players[f]->p_PV<=0){
                                        ko=1;
                                        while(joueur_ko[ko_buffer]!=-1){
                                            ko_buffer++;
                                        }
                                        joueur_ko[ko_buffer]=f;
                                        players[f]->p_alive=0;
                                        players[f]->p_PV=0;
                                        ko_buffer=0;
                                    }
                                }
                            }
                        }
                    }else if(characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_type==2){
                        for(int f=0;f<nbPlayers;f++){
                            actual.first=players[f]->p_RowPos;
                            actual.second=players[f]->p_ColumnPos;
                            if(get_spell(grid,players,(*library)->l_Buffer,actual,spell_buffer,characters,nbtours%nbPlayers) && players[f]->p_alive){
                                if(((rand()%100)+1)<=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_success){
                                    players[f]->p_PV-=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_damage;
                                    if(players[f]->p_PV<=0){
                                        ko=1;
                                        while(joueur_ko[ko_buffer]!=-1){
                                            ko_buffer++;
                                        }
                                        joueur_ko[ko_buffer]=f;
                                        players[f]->p_alive=0;
                                        players[f]->p_PV=0;
                                        ko_buffer=0;
                                    }
                                }
                            }
                        }
                    }else{
                        for(int f=0;f<nbPlayers;f++){
                            if(players[f]->p_RowPos==target.first && players[f]->p_ColumnPos==target.second && players[f]->p_alive && (((rand()%100)+1)<=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_success)){
                                players[f]->p_PV+=characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_damage;
                                if(players[f]->p_PV>characters[players[f]->p_character]->c_PV){
                                        players[f]->p_PV=characters[players[f]->p_character]->c_PV;
                                }
                            }
                        }
                    }
                }else{
                    actual.first=players[nbtours%nbPlayers]->p_RowPos;
                    actual.second=players[nbtours%nbPlayers]->p_ColumnPos;
                    sprite_display(library,grid,players,nbPlayers,(*library)->l_Melee[players[nbtours%nbPlayers]->p_character],actual,2,150,1);
                    spell=0;
                    for(int f=0;f<nbPlayers;f++){
                        if(players[f]->p_RowPos==target.first && players[f]->p_ColumnPos==target.second){
                            players[f]->p_PV-=15;
                            if(players[f]->p_PV<=0){
                                ko=1;
                                while(joueur_ko[ko_buffer]!=-1){
                                    ko_buffer++;
                                }
                                joueur_ko[ko_buffer]=f;
                                players[f]->p_alive=0;
                                players[f]->p_PV=0;
                                ko_buffer=0;
                            }
                        }
                    }
                }
            }
            if(moving==0)
            {
                if(spell_buffer==-1){
                    path_possible(library,players,grid,nbtours%nbPlayers,pair_,0,nbPlayers);      //Montrer chemin dispo
                    if((mouse_b&2)){
                        moving=1;
                    }
                }
                if((mouse_b&2) && spell_buffer!=-1 && players[nbtours%nbPlayers]->p_PA>0){
                    if(spell_buffer!=-2){
                        if(get_spell(grid,players,(*library)->l_Buffer,pair_,spell_buffer,characters,nbtours%nbPlayers) || characters[players[nbtours%nbPlayers]->p_character]->c_spell[spell_buffer]->s_type==2){//sprite_display(library, (*library)->l_Melee[players[0]->p_character], pair_, 5);
                            target=pair_;
                            spell=1;
                        }
                    }else{
                        if(get_melee(pair_,players,nbtours%nbPlayers)){
                            target=pair_;
                            spell=1;
                        }
                    }
                }
                if((mouse_b&1) && pair_.first==12)
                {
                    spell_buffer=-1;
                    switch(pair_.second)
                    {
                    case 9:
                        spell_buffer=-2;
                        break;
                    case 11:
                        spell_buffer=0;
                        break;
                    case 13:
                        spell_buffer=1;
                        break;
                    case 15:
                        spell_buffer=2;
                        break;
                    case 17:
                        spell_buffer=3;
                        break;
                    default:
                        break;
                    }
                    rest(100);
                }
                if(spell_buffer!=-1)
                {
                    switch(spell_buffer)
                    {
                    case -2:
                        rect((*library)->l_Buffer,9*50,12*50,10*50,13*50,makecol(255,174,201));
                        break;
                    case 0:
                        rect((*library)->l_Buffer,11*50,12*50,12*50,13*50,makecol(255,174,201));
                        break;
                    case 1:
                        rect((*library)->l_Buffer,13*50,12*50,14*50,13*50,makecol(255,174,201));
                        break;
                    case 2:
                        rect((*library)->l_Buffer,15*50,12*50,16*50,13*50,makecol(255,174,201));
                        break;
                    case 3:
                        rect((*library)->l_Buffer,17*50,12*50,18*50,13*50,makecol(255,174,201));
                        break;
                    default:
                        break;
                    }
                    if(spell_buffer!=-2)
                        spell_display_range(grid,players,(*library)->l_Buffer,pair_,spell_buffer, characters,nbtours%nbPlayers);
                    else
                        melee(grid,players,library, nbtours%nbPlayers);
                }
            }
            else
            {
                path_possible(library,players,grid,nbtours%nbPlayers,pair_,1,nbPlayers);
                moving=0;
            }
            if(is_over(players,nbPlayers)==1 && ko==0)
            {
                ranking[deadPlayers]=players[nbtours%nbPlayers];
                choix=finito(library,grid,ranking,nbPlayers);
                break;
            }
            if((actualTime-currentTime)/(CLOCKS_PER_SEC/1000)>TIMING)       //Passage au tour suivant si TIMING écoulé
            {
                do{
                    players[nbtours%nbPlayers]->p_PM=characters[players[nbtours%nbPlayers]->p_character]->c_PM;
                    players[nbtours%nbPlayers]->p_PA=characters[players[nbtours%nbPlayers]->p_character]->c_PA;
                    nbtours++;
                    spell_buffer=-1;
                }while(players[nbtours%nbPlayers]->p_PV<=0);
                currentTime=clock();
            }
            else if(pair_.first==13 && pair_.second==23)        //Passage tour suivant si clic suivant (bas à droite)
            {
                masked_blit((*library)->l_Next[1],(*library)->l_Buffer,0,0,50*23,50*13,SCREEN_W,SCREEN_H);
                if(mouse_b&1)
                {
                    while(mouse_b&1);
                    do{
                        players[nbtours%nbPlayers]->p_PM=characters[players[nbtours%nbPlayers]->p_character]->c_PM;
                        players[nbtours%nbPlayers]->p_PA=characters[players[nbtours%nbPlayers]->p_character]->c_PA;
                        nbtours++;
                        spell_buffer=-1;
                    }while(players[nbtours%nbPlayers]->p_PV<=0);
                    currentTime=clock();
                }
            }
            else masked_blit((*library)->l_Next[0],(*library)->l_Buffer,0,0,50*23,50*13,SCREEN_W,SCREEN_H);
            on_top_display(library,grid,players,nbPlayers,1);
            blit((*library)->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        actualTime=clock();
    }while(!key[KEY_ESC]);      //Tant que l'on appuie pas sur ECHAP
    stop_sample((*library)->l_Game);
    return(choix);
}

void write_map()        //SSP de complétion de la map (Utiliser seulement si l'on souhaite modifier la config de la map)
{
    int tab[14][24]
        = { { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, 3, 3, 3, 3, 1, 1 },
            { -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 4, 1, 1 },
            { -5, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
            { -5, 0, 0, -7, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
            { -5, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
            { 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4, 1, 1 },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
            { 2, 2, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, -4, 0, 0, 1, 1, 1 },
            { 2, 2, 2, 0, 0, -3, 0, 0, -5, -5, -5, -5, -5, 0, 0, 0, 0, -4, -4, 0, 0, 0, 1, 1 },
            { 2, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
            { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
            { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
            { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 } };

    FILE *file;

    file = fopen ("config/map/plain.txt", "wb");
    if (!file)
        puts("Probleme écriture fichier");

    for(int i=0; i<14; i++)
    {
        for(int j=0; j<24; j++)
            fprintf(file,"%d\t", tab[i][j]);
        fprintf(file,"\n");
    }
    fclose (file);

    for(int i=0; i<14; i++)
    {
        for(int j=0; j<24; j++)
            printf("%d\t", tab[i][j]);
        printf("\n");
    }
}

void initialization_map(t_cell**** grid, char* string)      //SSP d'initialisation de la map
{
    //Déclaration des variables
    int tab[14][24];
    char buffer[TAILLE_MAX]="";
    sprintf(buffer,"config/map/%s.txt",string);

    //Lecture du fichier
    FILE* file=fopen(buffer, "rb");
    if(!file)
        puts("Probleme lecture fichier");
    for(int i=0; i<14; i++)
    {
        for(int j=0; j<24; j++)
            fscanf(file,"%d\t", &tab[i][j]);
        fscanf(file,"\n");
    }
    fclose(file);

    //Complétion de la map
    for(int i=0; i<14; i++)
        for(int j=0; j<24; j++)
            (*grid)[i][j]->cl_availability=tab[i][j];
}

BITMAP* find_element(t_library** library, int nb)       //Trouve la sprite associé à un nom
{
    for(int i=0; i<ELEMENT; i++)
        if((*library)->l_PlainInfo[i]->mp_name==nb)
            return (*library)->l_PlainInfo[i]->mp_info;
    return 0;
}

void color_path(int row, int column, BITMAP* buffer, int rgb)       //SSP d'application d'un filtre de couleur sur une case spécifique
{
    int pixel;
    for(int x=column*50+1;x<(column+1)*50;x++)
        for(int y=row*50+1;y<(row+1)*50;y++)
        {
            pixel=getpixel(buffer,x,y);
            switch(rgb)
            {
            case 0:
                putpixel(buffer,x,y,makecol(getr(pixel),getg(pixel)/2,getb(pixel)/2));
                break;
            case 1:
                putpixel(buffer,x,y,makecol(getr(pixel)/2,getg(pixel),getb(pixel)/2));
                break;
            case 2:
                putpixel(buffer,x,y,makecol(getr(pixel)/2,getg(pixel)/2,getb(pixel)));
                break;
            case 3:
                putpixel(buffer,x,y,makecol(getr(pixel),getg(pixel)/2,getb(pixel)));
                break;
            case 4:
                putpixel(buffer,x,y,makecol(getr(pixel)/2,getg(pixel)/2,getb(pixel)/2));
                break;
            default:
                putpixel(buffer,x,y,makecol(getr(pixel),getg(pixel),getb(pixel)));
                break;
            }
        }
}

t_pair get_cell(int x, int y)       //SSP retournant la case de coordonnées x et y
{
    t_pair pair_;
    pair_.first = y/50;
    pair_.second = x/50;
    return pair_;
}

void spell_display_range(t_cell**** grid, t_player** players, BITMAP* buffer, t_pair coords, int nb_spell, t_character** characters, int nb_player)         //Code montre case touchable par sort
{
    switch(characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_type)
    {
        case 0:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){
                color_path(i+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,buffer,1);
                color_path(-i+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,buffer,1);
                color_path(players[nb_player]->p_RowPos,i+players[nb_player]->p_ColumnPos,buffer,1);
                color_path(players[nb_player]->p_RowPos,-i+players[nb_player]->p_ColumnPos,buffer,1);
            }
            break;
        case 1:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){
                color_path(i+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,buffer,1);
                color_path(-i+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,buffer,1);
                color_path(players[nb_player]->p_RowPos,i+players[nb_player]->p_ColumnPos,buffer,1);
                color_path(players[nb_player]->p_RowPos,-i+players[nb_player]->p_ColumnPos,buffer,1);
            }
            break;
        case 2:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){
                for(int j=players[nb_player]->p_RowPos-i;j<=players[nb_player]->p_RowPos+i;j++){
                    if(j>=players[nb_player]->p_RowPos){
                        color_path(j,players[nb_player]->p_ColumnPos+(players[nb_player]->p_RowPos+i-j),buffer,1);
                        color_path(j,players[nb_player]->p_ColumnPos-(players[nb_player]->p_RowPos+i-j),buffer,1);
                    }else{
                        color_path(j,players[nb_player]->p_ColumnPos+(players[nb_player]->p_RowPos-i-j),buffer,1);
                        color_path(j,players[nb_player]->p_ColumnPos-(players[nb_player]->p_RowPos-i-j),buffer,1);
                    }
                }
            }
            break;
        default:
            break;
    }
}

int get_spell(t_cell**** grid, t_player** players, BITMAP* buffer, t_pair coords, int nb_spell, t_character** characters, int nb_player){
    int good=0;
    switch(characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_type)
    {
        case 0:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){

                if((coords.first==(-i+players[nb_player]->p_RowPos) || coords.first==(i+players[nb_player]->p_RowPos)) && (coords.second==players[nb_player]->p_ColumnPos)){
                    good=1;
                }
                if((coords.second==(-i+players[nb_player]->p_ColumnPos) || coords.second==(i+players[nb_player]->p_ColumnPos)) && (coords.first==players[nb_player]->p_RowPos)){
                    good=1;
                }
            }
            break;
        case 1:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){
                if((coords.first==(-i+players[nb_player]->p_RowPos) || coords.first==(i+players[nb_player]->p_RowPos)) && (coords.second==players[nb_player]->p_ColumnPos)){
                    good=1;
                }
                if((coords.second==(-i+players[nb_player]->p_ColumnPos) || coords.second==(i+players[nb_player]->p_ColumnPos)) && (coords.first==players[nb_player]->p_RowPos)){
                    good=1;
                }
            }
            break;
        case 2:
            for(int i=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMin;i<=characters[players[nb_player]->p_character]->c_spell[nb_spell]->s_RangeMax;i++){
                for(int j=players[nb_player]->p_RowPos-i;j<=players[nb_player]->p_RowPos+i;j++){
                    if(j>=players[nb_player]->p_RowPos){
                        if(coords.first==j && (coords.second==players[nb_player]->p_ColumnPos+(players[nb_player]->p_RowPos+i-j) || coords.second==players[nb_player]->p_ColumnPos-(players[nb_player]->p_RowPos+i-j)))
                            good=1;
                    }else{
                        if(coords.first==j && (coords.second==players[nb_player]->p_ColumnPos-(players[nb_player]->p_RowPos-i-j) || coords.second==players[nb_player]->p_ColumnPos+(players[nb_player]->p_RowPos-i-j)))
                            good=1;
                    }
                }
            }
            break;
        default:
            break;
    }
    return(good);
}


void melee(t_cell**** grid, t_player** players, t_library** library, int nb_player)      //Si ennemi à côté tape en mélée
{
    color_path(1+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,(*library)->l_Buffer,1);
    color_path(-1+players[nb_player]->p_RowPos,players[nb_player]->p_ColumnPos,(*library)->l_Buffer,1);
    color_path(players[nb_player]->p_RowPos,1+players[nb_player]->p_ColumnPos,(*library)->l_Buffer,1);
    color_path(players[nb_player]->p_RowPos,-1+players[nb_player]->p_ColumnPos,(*library)->l_Buffer,1);
}

void sprite_display(t_library** library, t_cell**** grid, t_player** players, int nbPlayers, BITMAP* sprites, t_pair coords, int exit, int delay, int on_top)       //SSP d'animation d'une sprite (bloquant)
{
    //Déclaratino des variables
    int repertory[20] = {0};
    int cursor=1;
    repertory[0]=0;
    for(int i=0; i<sprites->w; i++)
        if(makecol(0,255,0)==getpixel(sprites,i,0))
        {
            repertory[cursor]=i+1;
            cursor++;
        }
    repertory[cursor]=-1;
    cursor=0;

    //Boucle d'affichage
    do
    {
        blit((*library)->l_Buffer,(*library)->l_Buffer2,0,0,0,0,SCREEN_W,SCREEN_H);
        if(repertory[cursor+1]!=-1) masked_blit(sprites,(*library)->l_Buffer2,repertory[cursor],0,coords.second*50,(coords.first+1)*50-sprites->h,repertory[cursor+1]-repertory[cursor]-1,64);
        else masked_blit(sprites,(*library)->l_Buffer2,repertory[cursor],0,coords.second*50,(coords.first+1)*50-sprites->h,sprites->w-repertory[cursor]-1,64);
        if(on_top==1) on_top_display(library,grid,players,nbPlayers,2);
        blit((*library)->l_Buffer2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        cursor++;
        if(repertory[cursor]==-1)
        {
            cursor=0;
            exit--;
        }
        rest(delay);
    }while(exit>0);
}

int get_melee(t_pair coords, t_player** players, int nb_player){
    int good=0;
    if(coords.first==players[nb_player]->p_RowPos && ((coords.second==players[nb_player]->p_ColumnPos+1)||(coords.second==players[nb_player]->p_ColumnPos-1)))
        good=1;
    if(coords.second==players[nb_player]->p_ColumnPos && ((coords.first==players[nb_player]->p_RowPos+1)||(coords.first==players[nb_player]->p_RowPos-1)))
        good=1;
    return(good);
}

int is_over(t_player** players, int nbPlayers)      //Retourne 1 s'il ne reste plus qu'un joueur en vie
{
    int cpt=0;
    for(int i=0; i<nbPlayers; i++)
        if(players[i]->p_alive==1)
            cpt++;
    return (cpt!=1) ? 0 : 1;
}

int finito(t_library** library, t_cell**** grid, t_player** players, int nbPlayers)     //Ecran de fin
{
    //Déclaratino des variables
    t_pair pair_;
    pair_.first=8; pair_.second=11;
    int quitter=0, choix;
    //Affichage
    blit((*library)->l_MenuBackground,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    textprintf_ex((*library)->l_Buffer,font,SCREEN_W/2-(strlen(" a remporte la partie ^^")+strlen(players[nbPlayers-1]->p_name))*3,SCREEN_H/3,makecol(0,0,0),-1,"%s a remporte la partie ^^",players[nbPlayers-1]->p_name);
    for(int i=0; i<nbPlayers-1; i++)
        textprintf_ex((*library)->l_Buffer,font,SCREEN_W/2-(strlen("%d . ")+strlen(players[i]->p_name))*3,SCREEN_H*2/3+i*15,makecol(0,0,0),-1,"%d . %s",i+2,players[i]->p_name);

    //Boucle d'affichage
    do{
        sprite_display(library,grid,players,nbPlayers,(*library)->l_Melee[players[nbPlayers-1]->p_character],pair_,1,150,0);
        rest(25);
    }while(!key[KEY_ESC]);
    while(key[KEY_ESC]);
    do{
        clear((*library)->l_Buffer);
        blit((*library)->l_MenuBackground,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        for(int i=0;i<6;i+=2){
            if(mouse_x>((SCREEN_W/2)-((*library)->l_MenuLaunchButton[i]->w/2)) && mouse_x<((SCREEN_W/2)+((*library)->l_MenuLaunchButton[i]->w/2)) && mouse_y>((SCREEN_H/2)-((*library)->l_MenuLaunchButton[i]->h/2)+(i-3)*60) && mouse_y<((SCREEN_H/2)+((*library)->l_MenuLaunchButton[i]->h/2)+(i-3)*60)){
                masked_blit((*library)->l_MenuLaunchButton[i+1],(*library)->l_Buffer,0,0,((SCREEN_W/2)-((*library)->l_MenuLaunchButton[i+1]->w/2)),((SCREEN_H/2)-((*library)->l_MenuLaunchButton[i+1]->h/2))+(i-3)*60,SCREEN_W,SCREEN_H);
                if(mouse_b&1){
                    quitter=1;
                    choix=i/2;
                }
            }else{
                masked_blit((*library)->l_MenuLaunchButton[i],(*library)->l_Buffer,0,0,((SCREEN_W/2)-((*library)->l_MenuLaunchButton[i]->w/2)),((SCREEN_H/2)-((*library)->l_MenuLaunchButton[i]->h/2))+(i-3)*60,SCREEN_W,SCREEN_H);
            }
        }
        masked_blit((*library)->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }while(!quitter);
    return(choix);
}

void player_display(t_library** library, t_player** players, t_character** character, int nbPlayers, int current)        //SSP d'affichage des infos des joueurs
{
    for(int i=0; i<nbPlayers; i++)
    {
        if(players[i]->p_name==players[current]->p_name)
            textprintf_ex((*library)->l_Buffer,font,50*0,50*12+25*i,makecol(255,255,0),-1,"%s",players[i]->p_name);
        else
            textprintf_ex((*library)->l_Buffer,font,50*0,50*12+25*i,makecol(0,0,0),-1,"%s",players[i]->p_name);
        textprintf_ex((*library)->l_Buffer,font,50*0,50*12+25*i+10,makecol(0,0,0),-1,"PV : %d/%d",players[i]->p_PV,character[players[i]->p_character]->c_PV);
        textprintf_ex((*library)->l_Buffer,font,50*2,50*12+25*i+10,makecol(0,0,0),-1,"PM : %d/%d",players[i]->p_PM,character[players[i]->p_character]->c_PM);
        textprintf_ex((*library)->l_Buffer,font,50*4,50*12+25*i+10,makecol(0,0,0),-1,"PA : %d/%d",players[i]->p_PA,character[players[i]->p_character]->c_PA);
    }
}

void on_top_display(t_library** library, t_cell**** grid, t_player** players, int nbPlayers, int buffer)
{
    for(int i=0; i<nbPlayers; i++)
    {
        if((*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos]->cl_availability == -6 || (*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos]->cl_availability == -5 || (*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos]->cl_availability == -7)
        {
            if(buffer==1)
                masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos]->cl_availability),(*library)->l_Buffer,0,0,50*players[i]->p_ColumnPos,50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
            else
                masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos]->cl_availability),(*library)->l_Buffer2,0,0,50*players[i]->p_ColumnPos,50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
        }
        if(is_valid(players[i]->p_RowPos,players[i]->p_ColumnPos-1))
            if((*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-1]->cl_availability == -7)
            {
                if(buffer==1)
                    masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-1]->cl_availability),(*library)->l_Buffer,0,0,50*(players[i]->p_ColumnPos-1),50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
                else
                    masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-1]->cl_availability),(*library)->l_Buffer2,0,0,50*(players[i]->p_ColumnPos-1),50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
            }
        if(is_valid(players[i]->p_RowPos,players[i]->p_ColumnPos-2))
            if((*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-2]->cl_availability == -7)
            {
                if(buffer==1)
                    masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-2]->cl_availability),(*library)->l_Buffer,0,0,50*(players[i]->p_ColumnPos-2),50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
                else
                    masked_blit(find_element(library,(*grid)[players[i]->p_RowPos][players[i]->p_ColumnPos-2]->cl_availability),(*library)->l_Buffer2,0,0,50*(players[i]->p_ColumnPos-2),50*players[i]->p_RowPos,SCREEN_W,SCREEN_H);
            }
    }
}

void bottom_display(t_library** library, t_player** players, t_character** characters, int current)
{
    masked_blit((*library)->l_Control[players[current]->p_character],(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    textprintf_ex((*library)->l_Buffer,font,50*7+25,50*12+7,makecol(255,255,255),-1,"%d",players[current]->p_PM);
    textprintf_ex((*library)->l_Buffer,font,50*7+25,50*12+22,makecol(255,255,255),-1,"%d",players[current]->p_PA);
    textprintf_ex((*library)->l_Buffer,font,50*7+25,50*12+39,makecol(255,255,255),-1,"%d",players[current]->p_PV);
    for(int i=0; i<4; i++)
    {
        textprintf_ex((*library)->l_Buffer,font,50*11+i*100,50*13+5,makecol(255,255,255),-1,"dmg: %d",characters[players[current]->p_character]->c_spell[i]->s_damage);
        textprintf_ex((*library)->l_Buffer,font,50*11+i*100,50*13+20,makecol(255,255,255),-1,"win: %d %%",characters[players[current]->p_character]->c_spell[i]->s_success);
    }
}
