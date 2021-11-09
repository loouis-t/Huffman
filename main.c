//programme principal
#include "fonctions.h"

int c = 0;
FILE* fichier_source = NULL;

int main(int argc, char *argv[]){
  fichier_source = fopen("lorem.txt", "r");

  if (fichier_source != NULL) {
    //lire caractere par caractere
    do {
      c = fgetc(fichier_source);
      printf("%c", c);
    } while(c != EOF);

    fclose(fichier_source);

  } else {
    printf("Impossible d'ouvrir le fichier !");
  }
}

// COMPILATION:
// gcc -Wall main.c fonctions.c fonctions.h -o exec
