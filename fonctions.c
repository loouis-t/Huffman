//fonctions utilisées
#include "fonctions.h"
/*
int estVide(arbre a) {
    return (a == NULL);
}

int estFeuille(arbre a) {
    return (estVide(a->gauche) && estVide(a->droit));
}

arbre creerArbre(int somme_occ, arbre fg, arbre fd) {
    arbre ab = (arbre) malloc(sizeof(arbre));
    ab->gauche = fg;
    ab->droit = fd;
    ab->somme_occurrences = somme_occ;

    return ab;
}

maillon getFilsGauche(arbre a) {
    return a->gauche;
}

maillon getFilsDroit(arbre a) {
    return a->droit;
}*/

maillon creerMaillon(int c, int occ, int somme_occ, maillon fg, maillon fd, maillon suivant) {
    maillon m = malloc(128 * sizeof(maillon));
    m->caractere = c;
    m->occurrence = occ;
    m->somme_occurrences = somme_occ;
    m->gauche = fg;
    m->droit = fd;
    m->suivant = suivant;

    return m;
}

maillon getMaillonSuivant(maillon m) {
    return m->suivant;
}

maillon getFilsGauche(maillon m) {
    return m->gauche;    
}

maillon getFilsDroit(maillon m) {
    return m->droit;
}

int getCaractere(maillon m) {
    return m->caractere;
}

// pas tres beau mais:
// somme_ou_occ: 
//      --> 1         => retourne la somme des occurrences    (-1 si vide)
//      --> 2         => retourne l'occurrence                (-1 si vide)
//      --> sinon (0) => retourne celui different de -1
int getOccurrence(maillon m, int somme_ou_occ) {
    if (somme_ou_occ == 1)
    {
        return m->somme_occurrences;
    }
    else
    {
        if (somme_ou_occ == 2)
        {
            return m->occurrence;
        }
        else
        {
            if (m->somme_occurrences == -1)
            {
                return m->occurrence;
            }
            else
            {
                return m->somme_occurrences;
            }
        }
    }
}

// trier liste de maillons dans tableau de maillons (maillon*)
maillon* trierListeMaillons(maillon m) {
    maillon* tab = malloc(128 * sizeof(maillon)); // 128 caracteres differents dans ASCII
    int n = 0;
    // init tableau pour tri
    for (int i=0; i<128; ++i)
    {
        tab[i] = NULL;
    }

    // ajouter maillons dans tableau pour faciliter tri
    do {
        tab[n] = m;
        ++n;
        m = getMaillonSuivant(m);
    } while(m != NULL);

    // trier tableau (bubble sort)
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n-i; ++j)
        {
            if (((tab[j] != NULL) && (tab[j+1] != NULL)) && (getOccurrence(tab[j], 0) > getOccurrence(tab[j+1], 0)))
            {
                maillon temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
    free(m);
    return tab;
}

// nécessite fonction 'trierListeMaillons'
// init n = 0
// ************************************* PROBLEME: ++n impossible a passer en param ***************************************
maillon convertirTabMaillon(maillon* tab, int n) {
    if (tab[n] == NULL) 
    {
        return NULL;
    }
    else
    {
        if (tab[n+1] == NULL)
        {
            return creerMaillon(getCaractere(tab[n]), getOccurrence(tab[n], 2), getOccurrence(tab[n], 1), getFilsGauche(tab[n]), getFilsDroit(tab[n]), NULL);
        }
        else
        {
            ++n;
            return creerMaillon(getCaractere(tab[n-1]), getOccurrence(tab[n-1], 2), getOccurrence(tab[n-1], 1), getFilsGauche(tab[n-1]), getFilsDroit(tab[n-1]), convertirTabMaillon(tab, n));
        }
    }
}

void afficherListeMaillons(maillon m) {
    if (getCaractere(m) != -1)
    {
        printf("%d : ", getCaractere(m));
    }
    else 
    {
        printf("Somme des occurrences : ");
    }
    printf("%d\n", getOccurrence(m, 0));
    if (m->suivant != NULL) {
        afficherListeMaillons(m->suivant);
    }
}

// vérifier si le caractere a deja ete checké
int checkIfMaillon(int c, char* caracteres_distincts, int position) {
    if (caracteres_distincts[position] == '\0')
    {
        return 0;
    }
    else
    {
        if (caracteres_distincts[position] == c)
        {
            return 1;
        }
        else
        {
            return checkIfMaillon(c, caracteres_distincts, ++position);
        }
    }
}

// convertir FILE* en char (plus simple a manipuler)
char* convertirFileChar(char* fileName) {
    FILE* fichier_source = fopen(fileName, "r");         // ouvrir fichier txt
    char* chaine_temp;
    char* chaine_caracteres;
    if (fichier_source != NULL)
    {
        fseek(fichier_source, 0, SEEK_END);                 // position dernier caractere de FILE
        long int length = ftell(fichier_source);
        chaine_caracteres = malloc(length);                 // allouer cette taille a chaine_caracteres
        chaine_temp = malloc(length);                       // allouer cette taille a chaine_temp
        fseek(fichier_source, 0, SEEK_SET);                 // revenir au debut du fichier
        do {
            fgets(chaine_temp, length, fichier_source);
            strcat(chaine_caracteres, chaine_temp);

            // si saut de ligne, le rajouter dans la chaine
            while (fgetc(fichier_source) == '\n') {
                chaine_caracteres[strlen(chaine_caracteres)] = '\n';
            } 

            printf("Taille 'fichier_source' : %ld\n", length);
            printf("Taille 'chaine_caracteres' : %ld\n\n", strlen(chaine_temp));
        } while (fgetc(fichier_source) != EOF);
    }
    fclose(fichier_source);                                 // libérer FILE
    printf("chaine: %s\n", chaine_caracteres);
    free(chaine_temp);                                      // libérer chaine_temp
    return "fffffccccccccccccbbbbbbbbbbbbbddddddddddddddddeeeeeeeeeaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //return chaine_caracteres;
}

/*char* getDistinctsCaracters(char* chaine_caracteres, char* caracteres_distincts, int position_chaine) {
    int flag = 0; // le caractere n'a jamais ete vu
    if (position_chaine > strlen(chaine_caracteres))
    {
        return caracteres_distincts;
    }
    else
    {
        for (int i = 0; i < strlen(caracteres_distincts); ++i)
        {
            if (chaine_caracteres[position_chaine] == caracteres_distincts[i])
            {
                flag = 1;   // le caractere a deja ete vu
                break;
            }
        }
        if(flag == 0)       // si jamais vu ...
        {
            caracteres_distincts[strlen(caracteres_distincts)] = chaine_caracteres[position_chaine];   // ajouter caractere chaine dans liste des caracteres distincts
        }
        return getDistinctsCaracters(chaine_caracteres, caracteres_distincts, ++position_chaine);
    }
}*/

// recuperer liste de maillons [caractere, occurrence]
maillon countOccurrences(char* chaine_caracteres, char* caracteres_distincts, int position) {
    int n = position;       // commencer les tests a la position du caractere temoin
    char current_c;
    char first_c;
    int first_c_occ = 0;    // init à 1 pour ++ par la suite

    if (chaine_caracteres != NULL) {

        first_c = chaine_caracteres[position];  // stocker premier caractere (ascii) --> comparer par la suite
        if (first_c == '\0')                    // si c'est le signal de fin...
        {
            return NULL;
        }
        else
        {
            if (checkIfMaillon(first_c, caracteres_distincts, 0) == 0)          // si le caractere n'a pas deja ete checké
            {
                caracteres_distincts[strlen(caracteres_distincts)] = first_c;   // ajouter nouveau caractere a la liste des caracteres trouvables dans le texte
                do {
                    current_c = chaine_caracteres[n++];     // récupérer caractere un par un dans texte
                    if (current_c == first_c) {   // si le caractere observé est le meme que celui avec lequel on compare...
                        ++first_c_occ;                      // compter occurrences caractere
                    }
                } while(current_c != '\0');                 // '\0': signal de fin de chaine
                return creerMaillon(first_c, first_c_occ, -1, NULL, NULL, countOccurrences(chaine_caracteres, caracteres_distincts, ++position)); // creer maillon en rappelant la fonction (recursivité)
            }
            else {
                return countOccurrences(chaine_caracteres, caracteres_distincts, ++position);
            }
        }
    }
    else
    {
        return NULL;
    }
}


maillon construireArbreDeCodage(maillon m) {
    if (getMaillonSuivant(m) == NULL)
    {
        return m;   // si un seul maillon restant: terminé-->arbre construit
    }
    else
    {
        maillon next_m = getMaillonSuivant(m);                                              // retenir le maillon suivant               (lisibilité)
        int somme_frequences = getOccurrence(m, 0) + getOccurrence(next_m, 0);              // additionner occurrences                  (lisibilité)
        m = creerMaillon(-1, -1, somme_frequences, m, next_m, getMaillonSuivant(next_m));   // creer arbre avec deux premiers maillons
        maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);                   // trier cette chaine de maillons
        //printf("occ fg: %d\n", getOccurrence(getFilsGauche(m_sorted), 0));
        return construireArbreDeCodage(m_sorted);                                           // recursivité: rappel fonction
    }
}

/*void parcoursPrefixe(maillon m, char* binaryCode, int pos, int cote) {
    if (m != NULL)
    {
        binaryCode[pos++] = cote;
        if (getCaractere(m) != -1)      // si le premier noeud possede un caractere
        {
            binaryCode[pos] = '\0';     // terminer chaine de maillons
            printf("%c : %d : %s\n", getCaractere(m), getOccurrence(m, 2), binaryCode);
            --pos;
        }
        parcoursPrefixe(getFilsGauche(m), binaryCode, pos, 48);
        parcoursPrefixe(getFilsDroit(m), binaryCode, pos, 49);
    } 
    else 
    {
        binaryCode[pos] = '\0';
    }
}*/

char SUCCESS[10];

char* parcoursPrefixe(maillon m, char* binaryCode, int pos, int cote, int c_recherche) {
    //printf("%d : %s\n", pos, binaryCode);
    if (m != NULL)
    {
        binaryCode[pos++] = cote;
        if (getFilsGauche(m) == NULL && getFilsDroit(m) == NULL)
        {
            if (getCaractere(m) == c_recherche)
            {
                binaryCode[pos] = '\0';
                strcpy(SUCCESS, binaryCode); // copier contenu pointeur dans variable globale SUCCESS
                return binaryCode;
            }
            return binaryCode;
        }
        else
        {
            strcat(binaryCode, parcoursPrefixe(getFilsGauche(m), binaryCode, pos, 48, c_recherche));
            strcat(binaryCode, parcoursPrefixe(getFilsDroit(m), binaryCode, pos, 49, c_recherche));

            binaryCode[pos] = '\0';
            return binaryCode;
        }
    }
    else
    {
        binaryCode[pos+1] = '\0';
        return binaryCode;
    }
}

char* creerEnTeteHuffman(maillon liste_triee, maillon ab, char* chaine_encodee) {

    if (getMaillonSuivant(liste_triee) != NULL)
    {
        // convertir int en char* et concatener les infos voulues dans en-tete
        char* chaine_temp = malloc(1000);
        sprintf(chaine_temp, "%s%c%c%d%c%c", chaine_encodee, getCaractere(liste_triee), ':', getOccurrence(liste_triee, 0), ',', '\0'); 

        return creerEnTeteHuffman(getMaillonSuivant(liste_triee), ab, chaine_temp);
    }
    else
    {
        chaine_encodee[strlen(chaine_encodee)-1] = '\n';
        return chaine_encodee;
    }
}

void creerDocHuffman(maillon liste_triee, maillon arbre, char* fichierChar, char* fileName) {
    char* chaine_encodee = malloc(1000);
    chaine_encodee[0] = '\0'; //debug
    //sprintf(chaine_encodee, "%d%c%c", getOccurrence(arbre, 0), ',', '\0');      // convertir somme_occurrence (d'arbre complet) en char* + ajouter ',' + '\0'(signal fin de chaine)
    //chaine_encodee = creerEnTeteHuffman(liste_triee, arbre, chaine_encodee);    // creer entete permettant decompression
    //printf("entete: %s", chaine_encodee);

    // encoder la chaine
    //char* chaine_totale = parcoursPrefixe(arbre, malloc(10), -1, '\0', 'f');
    //free(tmp);
    for(int i=0; i<strlen(fichierChar); ++i)
    {
        char* tmp = parcoursPrefixe(arbre, malloc(10), -1, '\0', fichierChar[i]);
        free(tmp);
        strcat(chaine_encodee, SUCCESS);
    }
    printf("%s", chaine_encodee); // malloc(): invalid size (unsorted)

    FILE* fichier_compresse = fopen("essai_cmp.txt", "w");
    if (fichier_compresse != NULL)
    {
        fputs(chaine_encodee, fichier_compresse);
        fclose(fichier_compresse);
    }
}