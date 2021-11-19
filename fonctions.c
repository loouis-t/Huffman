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

int getOccurrence(maillon m) {
    if (m->somme_occurrences == -1)
    {
        return m->occurrence;
    }
    else
    {
        return m->somme_occurrences;
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
            if (((tab[j] != NULL) && (tab[j+1] != NULL)) && (getOccurrence(tab[j]) > getOccurrence(tab[j+1])))
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
// init n = -1
// ************************************* PROBLEME: ++n impossible a passer en param ***************************************
maillon convertirTabMaillon(maillon* tab, int n) {
    if (tab[n] != NULL)
    {
        if(tab[n+1] == NULL)
        {
            return NULL;
        }
        else
        {
            n++;
            return creerMaillon(getCaractere(tab[n]), getOccurrence(tab[n]), -1, NULL, NULL, convertirTabMaillon(tab, n));
        }
    }
    else
    {
        return NULL;
    }
}

void afficherListeMaillons(maillon m) {
    printf("%c : ", getCaractere(m));
    printf("%d\n", getOccurrence(m));
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
        free(m);
        return NULL;
    }
    else 
    {

        m = convertirTabMaillon(trierListeMaillons(m), 0);
        maillon next_m = getMaillonSuivant(m);
        int somme_frequences = getOccurrence(m) + getOccurrence(next_m);
        return creerMaillon(-1, -1, somme_frequences, m, next_m, construireArbreDeCodage(getMaillonSuivant(next_m)));
    }
}