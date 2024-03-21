#include "file.h"

int is_valid(int row, int col)      //Retourne 1 si la case est dans la grille
{
    if((row>=0)&&(row<14)&&(col>=0)&&(col<24))
        return 1;
    else return 0;
}

int is_unblocked(t_cell****grid, int row, int col)      //Retourne 1 si la case est accessible
{
    if((*grid)[row][col]->cl_availability<=0)
        return 1;
    else
        return 0;
}

void path_possible(t_library** library, t_player** players, t_cell**** grid, int nb_player, t_pair coords, int state, int nbPlayers)       //Appel de dijkstra
{
    int n=14*24;
    int u=players[nb_player]->p_ColumnPos+players[nb_player]->p_RowPos*24;
    players[nb_player]->p_PM-=dijkstra(library,grid,players,n,u,coords.second+coords.first*24, state, nb_player, nbPlayers);
    if(players[nb_player]->p_PM<=0) players[nb_player]->p_PM=0;      //Blindage
}

t_pair convert(int i)       //Converti un noeud en une case
{
    t_pair result;
    for(int j=1; j<12; j++)
        if(i%(24*j)<24)
        {
            result.first=j;
            result.second=(i%(24*(j)));
        }
    return result;
}

int grid_availability(t_cell**** grid, t_pair coords)       //Retourne 1 si case accessible
{
    if(is_valid(coords.first,coords.second))
    {
        if(is_unblocked(grid,coords.first,coords.second))
            return 1;
    }
    return 0;
}

int is_neighbor(int i, int j)       //Retourne 1 si la case j  est voisine directe à i
{
    if(j==i+1 || j==i-1 || j==i+24 || j==i-24) return 1;
    return 0;
}

int dijkstra(t_library** library, t_cell**** grid, t_player** players, int n, int startnode, int endnode, int state, int nb, int nbPlayers)        //Algorithme de chemin dijkstra
{
    //Déclaration des variables
    int cost[MAX_][MAX_],distance[MAX_],pred[MAX_];
    int visited[MAX_],count,mindistance,nextnode,i,j;

    t_pair pair_=convert(endnode);

    if(is_unblocked(grid,pair_.first,pair_.second)==1 && players[nb]->p_PM>0)   //Si il l'arrivée n'est pas un obstacle et qu'il reste des PM
    {
        //Complétion de la grille de cout
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(is_neighbor(i,j)==1 && grid_availability(grid,convert(j))==1)
                    cost[i][j]=1;
                else
                    cost[i][j]=INFINITY_;
            }

        //Initialisation
        for(i=0;i<n;i++)
        {
            distance[i]=cost[startnode][i];
            pred[i]=startnode;
            visited[i]=0;
        }
        distance[startnode]=0;
        visited[startnode]=1;
        count=1;

        //Boucle de l'algo dijkstra
        while(count<n-1)
        {
            mindistance=(int)INFINITY;      //Distance initialisée à INFINITY au début
            for(i=0;i<n;i++)
                if(distance[i]<mindistance&&!visited[i])        //Si pas visité et nouvelle distance minimale
                {
                    mindistance=distance[i];
                    nextnode=i;
                }
            visited[nextnode]=1;        //Marquage du noeud
            for(i=0;i<n;i++)
                if(!visited[i])     //Si noeud pas encore exploré
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                         distance[i]=mindistance+cost[nextnode][i];
                         pred[i]=nextnode;
                    }
            count++;
        }

        for(i=0;i<n;i++)
            if(i==endnode)      //Si noeud souhaité
            {
                if(distance[i]<=players[nb]->p_PM)      //Si PM suffisant
                {
                    if(state==1)        //Si déplacement
                    {
                        int tab1[20]={0};
                        int tab2[20]={0};
                        int cursor=0, temp=i;
                        tab1[cursor]=i;
                        cursor++;
                        j=i;

                        //Insertion des prédécesseurs dans le tableau
                        do{
                            j=pred[j];
                            tab1[cursor]=j;
                            cursor++;
                        }while(j!=startnode);
                        //Inversion du tableau
                        for(i=cursor-1,j=0;i>=0;i--,j++)
                            tab2[j] = tab1[i];
                        for(i=0;i<cursor;i++)
                            tab1[i]=tab2[i];

                        //Affichage du chemin
                        for (i=0;i<cursor;i++)
                        {
                            if(tab1[i]!=0)
                            {
                                pair_=convert(tab1[i]);
                                players[nb]->p_RowPos=pair_.first;
                                players[nb]->p_ColumnPos=pair_.second;
                                sprite_display(library,grid,players,nbPlayers,(*library)->l_Walk[players[nb]->p_character],pair_,1,50,1);
                            }
                        }
                        pair_=convert(endnode);
                        //Nouvelles coordonnées du joueur
                        players[nb]->p_RowPos=pair_.first;
                        players[nb]->p_ColumnPos=pair_.second;
                        return distance[temp];
                    }
                    else        //Si juste affichage
                    {
                        pair_=convert(i);
                        color_path(pair_.first,pair_.second,(*library)->l_Buffer,1);
                        j=i;
                        //Affichage du chemin
                        do{
                            j=pred[j];
                            pair_=convert(j);
                            color_path(pair_.first,pair_.second,(*library)->l_Buffer,1);
                        }while(j!=startnode);
                        return 0;
                    }
                }
            }
    }
    if(endnode>23 && endnode<288) color_path(pair_.first,pair_.second,(*library)->l_Buffer,0);      //Affiche case rouge si chemin impossible
    return 0;
}
