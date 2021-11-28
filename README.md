# Compression : Algrorithme de Huffman

## Compilation

```
gcc -Wall main.c fonctions.c fonctions.h -o huffman -lm
```

L'option ```-lm``` est permet de lier la librairie ```<maths.h>``` (qui ne fait pas partie des librairies standards de C) à la compilation.

## Execution

**Compression :**
```
./huffman -c fichier_a_compresser>
```

**Decompression :**
```
./huffman -d <fichier_a_decompresser> <nom_fichier_sortie>
```

**Aide :**
```
./huffman -h
```

## Fonctionnement

- **Compression**

Dans un premier temps, le programme ouvre le fichier en lecture seule et compte le nombre d'occurrence de chaque caractere (le nombre maximum de caractères est celui de la table ASCII, à savoir 128).
En même temps, chaque caractère est associé à son occurrence dans une liste chainée de maillons.
Cette liste est ensuite ordonnée grâce à un algoritme de tri (tri à bulles): pour cela la *liste chainée de maillons* est convertie en un *tableau de maillons* pour des raisons de simplicité. 
Ex: 
![tableau_maillons](./assets/tableau_maillons.png)
Ce tableau permet ensuite la construction d'un *arbre de codage*.
Ex:
![arbre_codage](./assets/arbre_codage.png)
