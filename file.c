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

    for(int i=0; i<2;i++)
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

    for(int i=0; i<CHARACTER; i++)
    {
        sprintf(buffer,"visual/chararacter/%s/card.bmp",(*characters)[i]->c_name);
        (*library)->l_MenuCharacters[i]=load_bitmap_check(buffer);
        sprintf(buffer,"visual/chararacter/%s/static.bmp",(*characters)[i]->c_name);
        (*library)->l_StaticCharacters[i]=load_bitmap_check(buffer);
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

    //library->l_Intro=load_sample_check("audio/menu.wav");
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

    for(int i=0; i<2;i++)
        destroy_bitmap((*library)->l_MenuLaunchButton[i]);

    destroy_bitmap((*library)->l_MenuNbTitle);

    for(int i=0; i<3;i++)
    {
        destroy_bitmap((*library)->l_MenuNbButton[i][0]);
        destroy_bitmap((*library)->l_MenuNbButton[i][1]);
    }

    destroy_bitmap((*library)->l_MenuPlayerTitle);

    for(int i=0; i<CHARACTER; i++)
        destroy_bitmap((*library)->l_MenuCharacters[i]);

    destroy_bitmap((*library)->l_Plain);
    for(int i=0; i<ELEMENT; i++)
        destroy_bitmap((*library)->l_PlainInfo[i]->mp_info);
    for(int i=0; i<CHARACTER; i++)
    {
        free((*library)->l_PlainInfo[i]);
    }
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
                if(keypressed()){       //Gestion saisie
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

t_player* dyna_player(int rowpos, int columnpos, int PV, int PM, int PA, int character, int alive, int j, char* string_pseudo)
{
    t_player* actual=(t_player*)malloc(sizeof(t_player));
    if(!actual)
        puts("!!! Probleme d'allocation !!!");
    if(j>2) actual->p_name=dynamic_char(string_pseudo);
    else actual->p_name=random_pseudo();
    actual->p_RowPos=rowpos;
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

void queue_empty(t_queue** queue_)
{
    while(*queue_)
        free(queue_dequeue(queue_));
    free(*queue_);
}

void display_map(t_library** library,t_cell**** grid, t_player** players, int nbPlayers)
{
    //Déclaration des variables
    clock_t prevTime=clock(), actualTime=clock();
    int nbtours=0;
    printf("C'est au tour du joueur %d qui s'appelle %s\n",nbtours%nbPlayers+1,players[nbtours%nbPlayers]->p_name);
    //Boucle d'affichage
    do
    {
        if((actualTime-prevTime)/(CLOCKS_PER_SEC/1000)>DURATION)    //Toutes les DURATION ms
        {
            blit((*library)->l_Plain,(*library)->l_Buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            for(int i=0;i<24;i++) vline((*library)->l_Buffer,i*50,0,SCREEN_H,makecol(255,255,255));
            for(int i=0;i<14;i++) hline((*library)->l_Buffer,0,i*50,SCREEN_W,makecol(255,255,255));
            for(int i=0; i<14; i++){
                for(int j=0; j<24; j++){
                    if((*grid)[i][j]->cl_availability<=-2 || (*grid)[i][j]->cl_availability>=2)
                    {
                        if((*grid)[i][j]->cl_availability==2)
                            masked_blit(find_element(library,(*grid)[i][j]->cl_availability),(*library)->l_Buffer,0,0,50*j-15,50*i-15,SCREEN_W,SCREEN_H);
                        else
                            masked_blit(find_element(library,(*grid)[i][j]->cl_availability),(*library)->l_Buffer,0,0,50*j,50*i,SCREEN_W,SCREEN_H);
                    }
                }
            }
            for(int k=0;k<nbPlayers;k++){
                colorPath(players[k]->p_RowPos,players[k]->p_ColumnPos,(*library)->l_Buffer);
                colorPath(players[k]->p_RowPos,players[k]->p_ColumnPos+1,(*library)->l_Buffer);
                colorPath(players[k]->p_RowPos,players[k]->p_ColumnPos+2,(*library)->l_Buffer);
            }
            for(int k=0;k<nbPlayers;k++){
                masked_blit((*library)->l_StaticCharacters[players[k]->p_character],(*library)->l_Buffer,0,0,(players[k]->p_ColumnPos)*50+3,50*(players[k]->p_RowPos+1)-(*library)->l_StaticCharacters[players[k]->p_character]->h,45,SCREEN_H);
            }
            /*
            if(changer de tours){
                nbtours++;
                printf("C'est au tour du joueur %d qui s'appelle %s\n",nbtours%nbPlayers+1,players[nbtours%nbPlayers]->p_name);
            }
            */
            blit((*library)->l_Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        actualTime=clock();
    }while(!key[KEY_ESC]);
}

void write_map()        //SSP de complétion de la map
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

BITMAP* find_element(t_library** library, int nb)
{
    for(int i=0; i<ELEMENT; i++)
        if((*library)->l_PlainInfo[i]->mp_name==nb)
            return (*library)->l_PlainInfo[i]->mp_info;
    return 0;
}

void colorPath(int row, int column, BITMAP* buffer){
    int pixel;
    for(int x=column*50+1;x<(column+1)*50;x++){
        for(int y=row*50+1;y<(row+1)*50;y++){
            pixel=getpixel(buffer,x,y);
            putpixel(buffer,x,y,makecol(getr(pixel),0,0));
        }
    }
    //return(buffer);
}
