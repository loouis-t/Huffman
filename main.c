//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){

    

    if(!strcmp(argv[1], "-c") && argv[2]) // compresser
    {
        // char* caracteresDistincts = ;
        // caracteresDistincts[0] = '\0';
        char* fichierChar = convertirFileChar(argv[2]);
        maillon m = countOccurrences(fichierChar, malloc(128*sizeof(char*)), 0, 0);           // compter les occurrences de chaque caractere
        puts("Occurrences OK");
        maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
        puts("Tri OK");
        // afficherListeMaillons(m_sorted);                                             // afficher
        maillon ab = construireArbreDeCodage(m_sorted);                                 // construire arbre a partir tableau de maillons
        puts("Arbre OK");
        printf("occurrences tot: %d\n", getOccurrence(ab, 0));
        printf("Compression...\n");
        creerDocHuffman(m_sorted, ab, fichierChar, argv[2]);
    }
    else if (!strcmp(argv[1], "-d") && argv[2] && argv[3])
    {
        puts("Décompression...");
        decompresserDocHuffman(argv[2], argv[3]);
    }
    else if (!strcmp(argv[1], "-h"))
    {
        printf("-c <fichier_a_compresser> : compresser un fichier\n");
        printf("-d <fichier_a_decompresser> <nom_fichier_sortie> : décompresser un fichier renommé en <nom_fichier_sortie>\n");
    }
    else
    {
        printf("Option invalide, saisissez << huffman -h >> pour plus d'informations");
    }


    
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    // parcoursPrefixe(ab, malloc(10), -1, '\0');

    
    puts("OK");

    
    puts("\nEND");

    // char* essai = parcourirArbre("1100", malloc(sizeof(char*)), ab, ab, 0);

    // printf("c: %c\n", essai[0]);

}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
