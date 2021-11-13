//fonctions utilisées
#include "fonctions.h"

int estVide(arbre a) {
    return (a == NULL);
}

int estFeuille(arbre a) {
    return (estVide(a->gauche) && estVide(a->droit));
}

arbre creerArbre(maillon m, arbre fg, arbre fd) {
    arbre ab = (arbre) malloc(sizeof(arbre));
    ab->gauche = fg;
    ab->droit = fd;
    ab->maillon = m;

    return ab;
}

arbre getFilsGauche(arbre a) {
    return a->gauche;
}

arbre getFilsDroit(arbre a) {
    return a->droit;
}

maillon creerMaillon(int c, int occ, maillon element) {
    maillon m = (maillon) malloc(sizeof(maillon));
    m->caractere = c;
    m->occurrence = occ;
    m->suivant = element;

    return m;
}

maillon getMaillonSuivant(maillon m) {
    return m->suivant;
}

int getCaractere(maillon m) {
    return m->caractere;
}

int getOccurrence(maillon m) {
    return m->occurrence;
}

void afficherListeMaillons(maillon m) {
    printf("%d : ", getCaractere(m));
    printf("%d\n", getOccurrence(m));
    if (m->suivant != NULL) {
        afficherListeMaillons(m->suivant);
    }
}

// vérifier si le caractere a deja ete checké
int checkIfMaillon(char* chaine_caracteres, int c, int position) {
    // peut etre amélioré: utliser iteratif pour eviter recalcul des caracteres distincts
    char* caracteres_distincts = getDistinctsCaracters(chaine_caracteres, malloc(128), 0, 0); // connaitre les différents caracteres de la chaine
    if (position > strlen(caracteres_distincts)) 
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
            return checkIfMaillon(caracteres_distincts, c, ++position);
        }
    }
}

// convertir FILE* en char (plus simple a manipuler)
char* convertirFileChar(char* fileName) {
    FILE* fichier_source = fopen(fileName, "r");         // ouvrir fichier txt
    char* chaine_caracteres;
    //int n = 0;
    if (fichier_source != NULL) 
    {
        fseek(fichier_source, 0, SEEK_END);                 // position dernier caractere de FILE
        long int length = ftell(fichier_source);
        chaine_caracteres = malloc(length);  // allouer cette taille a char
        fseek(fichier_source, 0, SEEK_SET);                 // revenir au debut du fichier

        fgets(chaine_caracteres, length, fichier_source);// placer FILE dans char*
    }
    fclose(fichier_source);                                 // libérer FILE

    return chaine_caracteres;
}

char* getDistinctsCaracters(char* chaine_caracteres, char* caracteres_distincts, int position_chaine, int position_distinct) {
    int flag = 0; // le caractere n'a jamais ete vu
    if (position_chaine > strlen(chaine_caracteres))
    {
        printf("%s\n", caracteres_distincts);
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
            caracteres_distincts[position_distinct] = chaine_caracteres[position_chaine];   // ajouter caractere chaine dans liste des caracteres distincts
            ++position_distinct;
        }
        return getDistinctsCaracters(chaine_caracteres, caracteres_distincts, ++position_chaine, position_distinct);
    }
}

// recuperer liste de maillons [caractere, occurrence]
maillon countOccurrences(char* chaine_caracteres) {
    int n = 0;
    char current_c;
    char first_c;
    int first_c_occ = 1; // init à 1 pour ++ par la suite
    maillon m = NULL;

    //printf("%s\n", chaine_caracteres);

    if (chaine_caracteres != NULL) {
        //printf("%s\n", chaine_caracteres);

        first_c = chaine_caracteres[n]; // stocker premier caractere (ascii) --> comparer par la suite
        if (first_c == '\0')            // si c'est le signal de fin...
        {
            return NULL;
        } 
        else
        {
            if (checkIfMaillon(chaine_caracteres, first_c, 0) == 1)    // si le caractere n'a pas deja ete checké
            {
                do {
                    current_c = chaine_caracteres[n++];     // récupérer caractere un par un dans texte
                    if (current_c == first_c) {             // si le caractere observé est le meme que celui avec lequel on compare...
                        first_c_occ++;                      // compter occurrences caractere
                    }
                } while(current_c != '\0');                 // '\0': signal de fin de chaine
            }
            /*printf("%c", first_c);*/
            memmove(chaine_caracteres, chaine_caracteres+1, strlen(chaine_caracteres));
            return creerMaillon((int)first_c, first_c_occ, countOccurrences(chaine_caracteres)); // creer maillon en rappelant la fonction (recursivité)
        }
    }
    else
    {
        return m;
    }
}
