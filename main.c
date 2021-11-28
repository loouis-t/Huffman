//programme principal
#include "fonctions.h"

int main(int argc, char *argv[]){

    if(argv[1])
    {
        if(!strcmp(argv[1], "-c") && argv[2] && argv[3])                                               // compresser
        {
            clock_t previous_millis = clock();

            // creer nouveau nom (nom fichier compressé)
            printf("Compression de %s...\n", argv[2]);

            char* fichierChar = convertirFileChar(argv[2]);
            maillon m = countOccurrences(fichierChar, malloc(128*sizeof(char*)), 0, 0);     // compter les occurrences de chaque caractere
            maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);               // trier liste chainée de maillons
            maillon ab = construireArbreDeCodage(m_sorted);                                 // construire arbre a partir tableau de maillons

            creerDocHuffman(m_sorted, ab, fichierChar, argv[2], argv[3]);

            clock_t current_millis = clock();
            float millis = (current_millis-previous_millis) *1000 / CLOCKS_PER_SEC;
            printf("Terminé (%.3fs).\n", millis/1000);
            printf("Taux de compression: %.1f%% (/!\\ Rapport nb caracteres (!= rapport poids)).\n", poids(argv[2], argv[3]));
        }
        else if (!strcmp(argv[1], "-d") && argv[2] && argv[3])
        {
            clock_t previous_millis = clock();
            printf("Décompression de %s...\n", argv[2]);
            decompresserDocHuffman(argv[2], argv[3]);
            clock_t current_millis = clock();
            float millis = (current_millis-previous_millis) *1000 / CLOCKS_PER_SEC;
            printf("Terminé (%.3fs).\n", millis/1000);

        }
        else if (!strcmp(argv[1], "-h"))
        {
            printf("-c <fichier_a_compresser> <nom_fichier_sortie> : compresser un fichier renommé en <nom_fichier_sortie>\n");
            printf("-d <fichier_a_decompresser> <nom_fichier_sortie> : décompresser un fichier renommé en <nom_fichier_sortie>\n");
        }
        else
        {
                printf("Option invalide, saisissez << ./huffman -h >> pour plus d'informations\n");
        }
    }
    else
    {
        printf("huffman: mauvaise utilisation\n");
        printf("Executez << ./huffman -h >> pour plus d'informations\n");
    }

    
    // afficherListeMaillons(ab); // afficher somme occurrences (val premier noeud arbre: unique maillone de la chaine)
    // parcoursPrefixe(ab, malloc(10), -1, '\0');


    // char* essai = parcourirArbre("1100", malloc(sizeof(char*)), ab, ab, 0);

    // printf("c: %c\n", essai[0]);

}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o huffman -lm
