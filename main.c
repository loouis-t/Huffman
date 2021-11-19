//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    maillon m = countOccurrences(convertirFileChar("lorem.txt"), malloc(128), 0);   // compter les occurrences de chaque caractere
    printf("OK 0\n");
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);
    afficherListeMaillons(m_sorted);
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
