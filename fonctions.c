//fonctions utilisées
#include "fonctions.h"

int estVide(arbre a) {
    return (a == NULL);
}

int estFeuille(arbre a) {
    return (estVide(a->gauche) && estVide(a->droit));
}

int getCaractere(arbre a) {
    return a->caractere;
}

int getOccurrence(arbre a) {
    return a->occurrence;
}

arbre creerArbre(int c, int occ, arbre fg, arbre fd) {
    arbre ab = (arbre) malloc(sizeof(arbre));
    ab->gauche = fg;
    ab->droit = fd;
    ab->caractere = c;
ab->occurrence = occ;

    return ab;
}

arbre getFilsGauche(arbre a) {
    return a->gauche;
}

arbre getFilsDroit(arbre a) {
    return a->droit;
}

arbre countOccurrences(FILE* fichier_source) {
    int caractere = 0;
    int ascii;
    int first_c_occ = 1; //init à 1 pour ++ par la suite
    arbre ab;

    if (fichier_source != NULL) {
        //lire caractere par caractere
        int first_c = (int)fgetc(fichier_source); //stocker premier caractere --> comparer par la suite
        do {
            caractere = fgetc(fichier_source); //récupérer caractere un par un texte
            ascii = (int)caractere; //recupérer sa valeur selon ascii
            if (ascii == first_c) {
                first_c_occ++;
            }
        } while(caractere != EOF); //EOF: End Of File
    }
}