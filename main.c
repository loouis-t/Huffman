//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    maillon m = countOccurrences(convertirFileChar("lorem.txt"), malloc(128), 0);   // compter les occurrences de chaque caractere
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
    afficherListeMaillons(m_sorted);                                                 // afficher

    maillon ab = construireArbreDeCodage(m_sorted);
    afficherListeMaillons(ab);
    parcoursPrefixe(ab, malloc(10), 48);
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
