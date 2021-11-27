//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    char* fichierChar = convertirFileChar("h2g2.txt");
    printf("fichierChar: %s\n", fichierChar);
    printf("taille fichierChar: %ld\n", strlen(fichierChar));
    char* caracteresDistincts = malloc(128*sizeof(char*));
    caracteresDistincts[0] = '\0';
    maillon m = countOccurrences(fichierChar, caracteresDistincts, 0, 0);           // compter les occurrences de chaque caractere
    puts("Occurrences OK");
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
    puts("Tri OK");
    // afficherListeMaillons(m_sorted);                                             // afficher
    maillon ab = construireArbreDeCodage(m_sorted);                                 // construire arbre a partir tableau de maillons
    puts("Arbre OK");
    printf("occurrences tot: %d\n", getOccurrence(ab, 0));
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    // parcoursPrefixe(ab, malloc(10), -1, '\0');

    printf("Compression...\n");
    creerDocHuffman(m_sorted, ab, fichierChar, "h2g2.txt");
    puts("OK");

    puts("Décompression...");
    decompresserDocHuffman("h2g2.tar");
    puts("\nEND");

    // char* essai = parcourirArbre("1100", malloc(sizeof(char*)), ab, ab, 0);

    // printf("c: %c\n", essai[0]);

}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
