#ifndef FONCTIONS_H //ne pas redéfinir ces structures et fonctions si elles le sont déjà
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

//definir structure caractere + son occurrence
typedef struct caractere caractere;
struct caractere {
  int caractere;
  int occurrence;
};

//definir structure noeud
typedef struct noeud noeud;
struct noeud {
  caractere c;
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
