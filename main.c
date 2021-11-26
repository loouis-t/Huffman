//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    char* fichierChar = convertirFileChar("debug.txt");
    printf("fichierChar: %s\n", fichierChar);
    maillon m = countOccurrences(fichierChar, malloc(128*sizeof(char*)), 0);        // compter les occurrences de chaque caractere
    puts("Occurrences OK");
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
    puts("Tri OK");
    // afficherListeMaillons(m_sorted);                                             // afficher
    maillon ab = construireArbreDeCodage(m_sorted);                                 // construire arbre a partir tableau de maillons
    puts("Arbre OK");
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    //parcoursPrefixe(ab, malloc(10), -1, '\0');

    printf("Compression...");
    creerDocHuffman(m_sorted, ab, fichierChar, "debug.txt");
    puts("OK");

    puts("Décompression...");
    decompresserDocHuffman("debug.tar");
    puts("\nEND");
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
