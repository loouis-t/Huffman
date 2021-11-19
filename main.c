//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    maillon m = countOccurrences(convertirFileChar("lorem.txt"), malloc(128), 0);   // compter les occurrences de chaque caractere
    afficherListeMaillons(m);
    
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), -1);               // trier liste chainée de maillons
    afficherListeMaillons(m_sorted);                                                // afficher

    /*maillon ab = construireArbreDeCodage(m_sorted);
    puts("OK 3");
    free(ab);*/
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
