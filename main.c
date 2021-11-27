//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){
    char* fichierChar = convertirFileChar("lorem.txt");
    printf("fichierChar: %s\n", fichierChar);
    printf("taille fichierChar: %ld\n", strlen(fichierChar));
    char* caracteresDistincts = malloc(128*sizeof(char*));
    caracteresDistincts[0] = '\0';
    maillon m = countOccurrences(fichierChar, caracteresDistincts, 0, 0);        // compter les occurrences de chaque caractere
    puts("Occurrences OK");
    maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
    puts("Tri OK");
    // afficherListeMaillons(m_sorted);                                             // afficher
    maillon ab = construireArbreDeCodage(m_sorted);                                 // construire arbre a partir tableau de maillons
    puts("Arbre OK");
    printf("occurrences tot: %d\n", getOccurrence(ab, 0));
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    //parcoursPrefixe(ab, malloc(10), -1, '\0');

    printf("Compression...\n");
    creerDocHuffman(m_sorted, ab, fichierChar, "lorem.txt");
    puts("\nOK");

    // int tableau[6] = { 0 };

    // tableau[0] = 10;
    // tableau[1] = 1;
    // tableau[2] = 3;
    // tableau[3] = 5;
    // tableau[4] = 2;
    // tableau[5] = 0;
    
    // trierTab(tableau, 6);

    

    puts("Décompression...");
    decompresserDocHuffman("lorem.tar");
    puts("\nEND");

    // char* essai = parcourirArbre("1100", malloc(sizeof(char*)), ab, ab, 0);

    // printf("c: %c\n", essai[0]);

}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec




void trierTab(int tab[], int taille) {
    int cpt = 1;

    while(cpt) {
        cpt = 0;
        for(int i=0; i<taille; ++i){
            if ((i+1<taille) && (tab[i] > tab[i+1]))
            {
                int temp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = temp;
                cpt = 1;
            }
        }
    }
    
    for(int i=0; i<taille; ++i) {
        printf("%d\n", tab[i]);
    }
}