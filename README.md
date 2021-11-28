# Compression : Algrorithme de Huffman

## Compilation

```
gcc -Wall main.c fonctions.c fonctions.h -o huffman -lm
```

L'option ```-lm``` est permet de lier la librairie ```<maths.h>``` (qui ne fait pas partie des librairies standards de C) à la compilation.

## Execution

**Compression :**
```./huffman -c fichier_a_compresser>```

**Decompression :**
```./huffman -d <fichier_a_decompresser> <nom_fichier_sortie>```

**Aide :**
```./huffman -h```

## Ordre

- Recupérer le contenu du texte à compresser,
- Lire les caracteres un par un et compter leur occurence dans le texte,
    - Ajouter les différents caractères dans une liste (struct caractere: c + occurrence) et chercher les occurrences dans le texte

    **OU**

    - Compter les occurences pour le premier caractere puis passer au suivant
        - /!\ ne pas recompter deux fois le même caractère
- Ajouter ces caractères dans un arbre binaire ordonné,
- 
