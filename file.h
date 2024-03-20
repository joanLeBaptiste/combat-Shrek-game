#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

/**Inclusion des librairies**/
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <math.h>

#define DURATION 80
#define TAILLE_MAX 1000
#define CHARACTER 4
#define ELEMENT 9

typedef struct mapinfo{
    int mp_name;
    BITMAP* mp_info;
}t_mapinfo;

typedef struct library{
    BITMAP* l_Buffer;
    BITMAP* l_Buffer2;

    BITMAP* l_MenuBackground;
    BITMAP* l_MenuLaunchButton[2];
    BITMAP* l_MenuNbTitle;
    BITMAP* l_MenuNbButton[3][2];
    BITMAP* l_MenuPlayerTitle;
    BITMAP* l_MenuCharacters[CHARACTER];
    BITMAP* l_StaticCharacters[CHARACTER];

    BITMAP* l_Plain;
    t_mapinfo** l_PlainInfo;

    SAMPLE* l_Intro;
}t_library;

typedef struct player
{
    int p_RowPos, p_ColumnPos;     //Position du joueur
    int p_PV, p_PM, p_PA;       //Caractéristiques du joueur
    int p_character;        //Classe du joueur
    char* p_name;       //Pseudo du joueur
    int p_alive;       //Vivant ?
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

/**Prototypes des sous_programmes**/
//file
void init_alleg();
char* dynamic_char(char[TAILLE_MAX]);
void initialization_library(t_library**,t_character***);
BITMAP *load_bitmap_check(char*);
SAMPLE* load_sample_check(char*);
void destroy_library(t_library**);
void initialization_character(t_character***);
void queue_enqueue(t_queue**, t_player*);
t_player* queue_dequeue(t_queue**);
char* random_pseudo();
void initialization_player(t_library**,t_character***,int,t_queue**);
t_player* dyna_player(int,int,int,int,int,int,int,int,char*);
void queue_display(t_queue**);
void queue_empty(t_queue**);
void display_map(t_library**,t_cell****, t_player**, int);
void write_map();
void initialization_map(t_cell****, char*);
BITMAP* find_element(t_library**, int);
void initialise_position(t_cell*** grid, t_player* player);
void colorPath(int row, int column, BITMAP* buffer);

//menu
void menu();
int menu_nb_players(t_library**);


#endif // FILE_H_INCLUDED
