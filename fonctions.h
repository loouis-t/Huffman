#ifndef FONCTIONS_H //ne pas redéfinir ces structures et fonctions si elles le sont déjà
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

//definir structure noeud
typedef struct noeud noeud;
struct noeud {
  int caractere; //vérifier type !
  int occurrence;
  noeud* gauche;
  noeud* droit;
};
typedef noeud* arbre; //associer arbre au pointeur de noeud

//definir les fonctions créées dans arbre.c
int estVide(arbre a);
int estFeuille(arbre a);
int getCaractere(arbre a);
int getOccurrence(arbre a);
arbre creerArbre(int c, int occ, arbre fg, arbre fd);
arbre getFilsGauche(arbre a);
arbre getFilsDroit(arbre a);
arbre countOccurrences(FILE* fichier_source);

#endif
