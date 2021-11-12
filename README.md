# projet-algo2
La compression : Algorithme de Huffman


## Ordre
- Recupérer le contenu du texte à compresser,
- Lire les caracteres un par un et compter leur occurence dans le texte,
    - Ajouter les différents caractères dans une liste (struct caractere: c + occurrence) et chercher les occurrences dans le texte

    **OU**

    - Compter les occurences pour le premier caractere puis passer au suivant
        - /!\ ne pas recompter deux fois le même caractère
- Ajouter ces caractères dans un arbre binaire ordonné,
- 
