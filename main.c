//programme principal
#include "fonctions.h"


int main(int argc, char *argv[]){
    maillon m = countOccurrences(convertirFileChar("lorem.txt"), malloc(128), 0);   // compter les occurrences de chaque caractere
    afficherListeMaillons(m);   // afficher la liste des maillons
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
