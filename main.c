//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){

    char* fichierChar = convertirFileChar("h2g2.txt");
    maillon m = countOccurrences(fichierChar, malloc(128), 0);                      // compter les occurrences de chaque caractere
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
    // afficherListeMaillons(m_sorted);                                                // afficher

    maillon ab = construireArbreDeCodage(m_sorted);
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    //parcoursPrefixe(ab, malloc(10), -1, '\0');

    creerDocHuffman(m_sorted, ab, fichierChar, "h2g2.txt");

    decompresserDocHuffman("h2g2.tar");
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
