//fonctions utilisées
#include "fonctions.h"

int estVide(arbre a) {
  return (a == NULL);
}

int estFeuille(arbre a) {
 return (estVide(a->gauche) && estVide(a->droit));
}

int getValeur(arbre a) {
 return a->valeur;
}

arbre creerArbre(int elt, arbre fg, arbre fd) {
  arbre ab = (arbre) malloc(sizeof(arbre));
  ab->gauche = fg;
  ab->droit = fd;
  ab->valeur = elt;

  return ab;
}

arbre getFilsGauche(arbre a) {
  return a->gauche;
}

arbre getFilsDroit(arbre a) {
  return a->droit;
}
