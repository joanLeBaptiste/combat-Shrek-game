#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

/**Inclusion des librairies**/
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <math.h>

#define DURATION 120
#define TAILLE_MAX 1000
#define CHARACTER 4
#define ELEMENT 9
#define TIMING 60000
#define INFINITY_ 9999
#define MAX_ 336

typedef struct mapinfo{
    int mp_name;
    BITMAP* mp_info;
}t_mapinfo;

typedef struct library{
    BITMAP* l_Buffer;
    BITMAP* l_Buffer2;

    BITMAP* l_MenuBackground;
    BITMAP* l_MenuLaunchButton[6];
    BITMAP* l_MenuNbTitle;
    BITMAP* l_MenuNbButton[3][2];
    BITMAP* l_MenuPlayerTitle;
    BITMAP* l_MenuCharacters[CHARACTER];

    BITMAP* l_Plain;
    t_mapinfo** l_PlainInfo;

    BITMAP* l_Static[CHARACTER];
    BITMAP* l_Ko[CHARACTER];
    BITMAP* l_Walk[CHARACTER];
    BITMAP* l_Melee[CHARACTER];
    BITMAP* l_Spell[CHARACTER][4];
    BITMAP* l_Control[CHARACTER];

    BITMAP* l_Next[2];

    SAMPLE* l_Intro;
    SAMPLE* l_Game;
}t_library;

typedef struct player
{
    int p_RowPos, p_ColumnPos;     //Position du joueur
    int p_PV, p_PM, p_PA;       //Caractéristiques du joueur
    int p_character;        //Classe du joueur
    char* p_name;       //Pseudo du joueur
    int p_alive;       //Vivant ?
    int p_frame;        //La frame du sprite actuel

}t_player;

typedef struct spell
{
    char* s_name;       //Nom du sort (pour les sprites)
    int s_RangeMin, s_RangeMax;     //Portée min et max
    int s_type;     //Type de sort (1:Ligne, 2:Cercle; 3: Zone)
    int s_damage, s_success;        //Dégats du sort +/- 33%; Chance de succès
}t_spell;

typedef struct character
{
    char* c_name;       //Nom de la classe (pour les sprites)
    int c_PV, c_PM, c_PA;       //Caractéristiques de la classe
    t_spell* c_spell[4];       //Liste des sorts dispo (Size==4 mais dyna <3)
}t_character;

typedef struct cell     //Tableau 2D de cellules
{
    int cl_parent_i, cl_parent_j;       //Coordonnées du parent
    double cl_f, cl_g, cl_h;     //f = g + h
    int cl_availability;        //Obstacle ??
}t_cell;

typedef struct queue_
{
    t_player* data;
    struct queue_* next;
}t_queue;

typedef struct pair_
{
    int first, second;
}t_pair;

/**Prototypes des sous_programmes**/
//Initialisation
void init_alleg();
void initialization_library(t_library**,t_character***);
void destroy_library(t_library**);
void initialization_character(t_character***);
void initialization_player(t_library**,t_character***,int,t_queue**);
void initialization_map(t_cell****, char*);
void initialise_position(t_cell*** grid, t_player* player);

//Usefull 1
char* random_pseudo();
t_player* dyna_player(int,int,int,int,int,int,int,int,char*);
void write_map();

//QUEUE
void queue_display(t_queue**);
void queue_empty(t_queue**);
void queue_enqueue(t_queue**, t_player*);
t_player* queue_dequeue(t_queue**);

//Boucle de jeu
int display_map(t_library**,t_cell****, t_player**, int,t_character**);

//Usefull 2
void sprite_display(t_library**, t_cell****, t_player**, int, BITMAP*, t_pair, int, int, int);
t_pair get_cell(int, int);
void color_path(int, int, BITMAP*, int);
BITMAP* find_element(t_library**, int);
BITMAP *load_bitmap_check(char*);
SAMPLE* load_sample_check(char*);
char* dynamic_char(char[TAILLE_MAX]);
void player_display(t_library**, t_player**, t_character**, int, int);
void on_top_display(t_library**, t_cell****, t_player**, int, int);
void bottom_display(t_library**, t_player**, t_character**, int);

//Sorts
void spell_display_range(t_cell****, t_player**, BITMAP*, t_pair, int, t_character**, int);
void melee(t_cell****, t_player**, t_library**, int);
int get_spell(t_cell****, t_player**, BITMAP*, t_pair, int, t_character**, int);
int get_melee(t_pair, t_player**, int);

//Fin
int is_over(t_player**, int);
int finito(t_library**, t_cell****, t_player**, int);

//Mouvement
void path_possible(t_library**,t_player**, t_cell****, int, t_pair, int, int);
int is_valid(int, int);
int dijkstra(t_library**, t_cell****, t_player**, int, int, int, int, int, int);
t_pair convert(int);
int grid_availability(t_cell****, t_pair);
int is_neighbor(int, int);

//Menu
int menu();
int menu_nb_players(t_library**);


#endif // FILE_H_INCLUDED
