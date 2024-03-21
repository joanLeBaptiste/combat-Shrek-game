#include "file.h"

int main()
{
    init_alleg();
    int choix=0;
    do{
        choix=menu();     //Appel de la boucle de menu
    }while(!key[KEY_ESC] && choix!=2);
    puts("Hello world");
    return 0;
}END_OF_MAIN();
