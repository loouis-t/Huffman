//programme principal
#include "fonctions.h"



int main(int argc, char *argv[]){
    FILE* fichier_source = fopen("lorem.txt", "r");
    //iterations.
    fclose(fichier_source); //libérer
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
