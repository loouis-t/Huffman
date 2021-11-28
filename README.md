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

