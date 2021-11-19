#ifndef FONCTIONS_H //ne pas redéfinir ces structures et fonctions si elles le sont déjà
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definir structure caractere + son occurrence
typedef struct element element;
struct element {
  int caractere;
  int occurrence;
  element* suivant;
};
typedef element* maillon; //associer maillon au pointeur de element

//definir structure noeud
typedef struct noeud noeud;
struct noeud {
  maillon maillon;
  noeud* gauche;
  noeud* droit;
};
typedef noeud* arbre; //associer arbre au pointeur de noeud

//definir les fonctions créées dans arbre.c
int estVide(arbre a);
int estFeuille(arbre a);
int getCaractere(maillon m);
int getOccurrence(maillon m);
arbre creerArbre(maillon m, arbre fg, arbre fd);
arbre getFilsGauche(arbre a);
arbre getFilsDroit(arbre a);
maillon creerMaillon(int c, int occ, maillon element);
maillon getMaillonSuivant(maillon m);
void afficherListeMaillons(maillon m);
maillon* trierListeMaillons(maillon m);
maillon convertirTabMaillon(maillon* tab, int n);
int checkIfMaillon(int c, char* caracteres_distincts, int position);
char* convertirFileChar(char* fileName);
//char* getDistinctsCaracters(char* chaine_caracteres, char* caracteres_distincts, int position_chaine);
maillon countOccurrences(char* chaine_caracteres, char* caracteres_distincts, int position);

#endif
