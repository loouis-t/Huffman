//fonctions utilisées
#include "fonctions.h"

int estVide(arbre a) {
    return (a == NULL);
}

int estFeuille(arbre a) {
    return (estVide(a->gauche) && estVide(a->droit));
}

int getCaractere(maillon m) {
    return m->caractere;
}

int getOccurrence(maillon m) {
    return m->occurrence;
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

maillon getMaillon(maillon m) {
    return m->suivant;
}

void afficherListeMaillons(maillon m) {
    printf("%d", getCaractere(m));
    printf("%d\n", getOccurrence(m));
    if (m->suivant != NULL) {
        afficherListeMaillons(m->suivant);
    }
}

maillon countOccurrences(FILE* fichier_source) {
    int caractere = 0;
    int first_c;
    int first_c_occ = 1; //init à 1 pour ++ par la suite
    maillon m = NULL;

    if (fichier_source != NULL) {

        first_c = (int)fgetc(fichier_source); //stocker premier caractere (ascii) --> comparer par la suite
        if (first_c == EOF) {
            return m;
        } else {
            do {
                caractere = fgetc(fichier_source); //récupérer caractere un par un dans texte
                if ((int)caractere == first_c) {
                    first_c_occ++; //compter occurrences caractere
                }
            } while(caractere != EOF); //EOF: End Of File
            return creerMaillon(first_c, first_c_occ, countOccurrences(*fichier_source[1]));
        }
    }
}
