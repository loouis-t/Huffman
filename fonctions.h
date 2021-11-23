#ifndef FONCTIONS_H //ne pas redéfinir ces structures et fonctions si elles le sont déjà
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// on appelle [maillon]: [caractere; occurrence][ptr_maillon_suiv] 
// definir structure caractere + son occurrence ou arbre contenant maillon1 + maillon2 + somme occurrences
// cette structure peut accueillir a la fois des [maillons] et des [arbres]
typedef struct element element;
struct element {
  int caractere;
  int occurrence;
  int somme_occurrences;
  element* gauche;
  element* droit;
  element* suivant;
};
typedef element* maillon;   // associer maillon au pointeur de element

//  definir les fonctions créées dans arbre.c

//int estVide(arbre a);
//int estFeuille(arbre a);
// arbre creerArbre(int somme_occ, arbre fg, arbre fd);
//char* getDistinctsCaracters(char* chaine_caracteres, char* caracteres_distincts, int position_chaine);

int getCaractere(maillon m);
int getOccurrence(maillon m, int somme_ou_occ);
maillon getFilsGauche(maillon m);
maillon getFilsDroit(maillon m);
maillon creerMaillon(int c, int occ, int somme_occ, maillon fg, maillon fd, maillon element);
maillon getMaillonSuivant(maillon m);
void afficherListeMaillons(maillon m);
maillon* trierListeMaillons(maillon m);
maillon convertirTabMaillon(maillon* tab, int n);
int checkIfMaillon(int c, char* caracteres_distincts, int position);
char* convertirFileChar(char* fileName);
maillon countOccurrences(char* chaine_caracteres, char* caracteres_distincts, int position);
maillon construireArbreDeCodage(maillon m);
void parcoursPrefixe(maillon m, char* binaryCode, int pos, int cote, int c_recherche);
char* creerEnTeteHuffman(maillon liste_triee, maillon ab, char* chaine_encodee);
//void parcoursPrefixe(maillon m, char* binaryCode, int pos, int cote);
void creerDocHuffman(maillon liste_triee, maillon arbre, char* fichierChar, char* fileName);

#endif
