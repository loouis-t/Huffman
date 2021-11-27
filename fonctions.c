//fonctions utilisées
#include "fonctions.h"
/*
int estVide(arbre a) {
    return (a == NULL);
}

int estFeuille(arbre a) {
    return (estVide(a->gauche) && estVide(a->droit));
}

arbre creerArbre(int somme_occ, arbre fg, arbre fd) {
    arbre ab = (arbre) malloc(sizeof(arbre));
    ab->gauche = fg;
    ab->droit = fd;
    ab->somme_occurrences = somme_occ;

    return ab;
}

maillon getFilsGauche(arbre a) {
    return a->gauche;
}

maillon getFilsDroit(arbre a) {
    return a->droit;
}*/

maillon creerMaillon(int c, int occ, int somme_occ, maillon fg, maillon fd, maillon suivant) {
    maillon m = malloc(128 * sizeof(maillon));
    m->caractere = c;
    m->occurrence = occ;
    m->somme_occurrences = somme_occ;
    m->gauche = fg;
    m->droit = fd;
    m->suivant = suivant;

    return m;
}

maillon getMaillonSuivant(maillon m) {
    return m->suivant;
}

maillon getFilsGauche(maillon m) {
    return m->gauche;    
}

maillon getFilsDroit(maillon m) {
    return m->droit;
}

int getCaractere(maillon m) {
    return m->caractere;
}

// pas tres beau mais:
// somme_ou_occ: 
//      --> 1         => retourne la somme des occurrences    (-1 si vide)
//      --> 2         => retourne l'occurrence                (-1 si vide)
//      --> sinon (0) => retourne celui different de -1
int getOccurrence(maillon m, int somme_ou_occ) {
    if (somme_ou_occ == 1)
    {
        return m->somme_occurrences;
    }
    else
    {
        if (somme_ou_occ == 2)
        {
            return m->occurrence;
        }
        else
        {
            if (m->somme_occurrences == -1)
            {
                return m->occurrence;
            }
            else
            {
                return m->somme_occurrences;
            }
        }
    }
}

// trier liste de maillons dans tableau de maillons (maillon*)
maillon* trierListeMaillons(maillon m) {
    maillon* tab = malloc(128 * sizeof(maillon)); // 128 caracteres differents dans ASCII
    int n = 0;
    // init tableau pour tri
    for (int i=0; i<128; ++i)
    {
        tab[i] = NULL;
    }

    // ajouter maillons dans tableau pour faciliter tri
    while(m != NULL) {
        tab[n] = m;
        ++n;
        m = getMaillonSuivant(m);
    }

    // trier tableau (bubble sort)
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n-i; ++j)
        {
            if (((tab[j] != NULL) && (tab[j+1] != NULL)) && (getOccurrence(tab[j], 0) > getOccurrence(tab[j+1], 0)))
            {
                maillon temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
    free(m);
    return tab;
}

// nécessite fonction 'trierListeMaillons'
// init n = 0
maillon convertirTabMaillon(maillon* tab, int n) {
    if (tab[n] == NULL) 
    {
        free(tab);
        return NULL;
    }
    else
    {
        if (tab[n+1] == NULL)
        {
            return creerMaillon(getCaractere(tab[n]), getOccurrence(tab[n], 2), getOccurrence(tab[n], 1), getFilsGauche(tab[n]), getFilsDroit(tab[n]), NULL);
        }
        else
        {
            ++n;
            return creerMaillon(getCaractere(tab[n-1]), getOccurrence(tab[n-1], 2), getOccurrence(tab[n-1], 1), getFilsGauche(tab[n-1]), getFilsDroit(tab[n-1]), convertirTabMaillon(tab, n));
        }
    }
}

void afficherListeMaillons(maillon m) {
    if (getCaractere(m) != -1)
    {
        printf("%d : ", getCaractere(m));
    }
    else 
    {
        printf("Somme des occurrences : ");
    }
    printf("%d\n", getOccurrence(m, 0));
    if (m->suivant != NULL) {
        afficherListeMaillons(m->suivant);
    }
}

// vérifier si le caractere a deja ete checké
int checkIfMaillon(int c, char* caracteres_distincts, int position) {
    if (caracteres_distincts[position] == '\0')
    {
        return 0;
    }
    else
    {
        if (caracteres_distincts[position] == c)
        {
            return 1;
        }
        else
        {
            return checkIfMaillon(c, caracteres_distincts, ++position);
        }
    }
}

// convertir FILE* en char (plus simple a manipuler)
char* convertirFileChar(char* fileName) {
    FILE* fichier_source = fopen(fileName, "r");            // ouvrir fichier txt
    char* chaine_caracteres;
    if (fichier_source != NULL)
    {
        fseek(fichier_source, 0, SEEK_END);                 // position dernier caractere de FILE
        long int length = ftell(fichier_source);            // connaitre taille fichier_source
        chaine_caracteres = malloc(length*sizeof(char*));   // allouer cette taille a chaine_caracteres
        fseek(fichier_source, 0, SEEK_SET);                 // revenir au debut du fichier
        fread(chaine_caracteres, length, sizeof(char*), fichier_source);    // recuperer texte de FILE* dans char*
    }
    fclose(fichier_source);                                 // libérer FILE
    //printf("chaine: %s\n", chaine_caracteres);
    return chaine_caracteres;
}

// recuperer liste de maillons [caractere, occurrence]
maillon countOccurrences(char* chaine_caracteres, char* caracteres_distincts, int position, int pos_char_dist) {
    int n = position;                           // commencer les tests a la position du caractere temoin
    char current_c;
    char first_c;
    int first_c_occ = 0;                        // init à 1 pour ++ par la suite

    if (chaine_caracteres != NULL) {

        first_c = chaine_caracteres[position];  // stocker premier caractere (ascii) --> comparer par la suite
        if (first_c == '\0')                    // si c'est le signal de fin...
        {
            return NULL;
        }
        else
        {

            if (checkIfMaillon(first_c, caracteres_distincts, 0) == 0)          // si le caractere n'a pas deja ete checké
            {
                caracteres_distincts[pos_char_dist] = first_c;      // ajouter nouveau caractere a la liste des caracteres trouvables dans le texte
                caracteres_distincts[pos_char_dist+1] = '\0';       // replacer signal de fin
                do {
                    current_c = chaine_caracteres[n++];     // récupérer caractere un par un dans texte
                    if (current_c == first_c) {             // si le caractere observé est le meme que celui avec lequel on compare...
                        ++first_c_occ;                      // compter occurrences caractere
                    }
                } while(current_c != '\0');                 // '\0': signal de fin de chaine
                return creerMaillon(first_c, first_c_occ, -1, NULL, NULL, countOccurrences(chaine_caracteres, caracteres_distincts, ++position, ++pos_char_dist)); // creer maillon en rappelant la fonction (recursivité)
            }
            else {
                return countOccurrences(chaine_caracteres, caracteres_distincts, ++position, pos_char_dist);
            }
        }
    }
    else
    {
        return NULL;
    }
}


maillon construireArbreDeCodage(maillon m) {
    if (m != NULL)
    {
        if (getMaillonSuivant(m) == NULL)
        {
            return m;   // si un seul maillon restant: terminé-->arbre construit
        }
        else
        {
            maillon next_m = getMaillonSuivant(m);                                              // retenir le maillon suivant               (lisibilité)
            int somme_frequences = getOccurrence(m, 0) + getOccurrence(next_m, 0);              // additionner occurrences                  (lisibilité)
            m = creerMaillon(-1, -1, somme_frequences, m, next_m, getMaillonSuivant(next_m));   // creer arbre avec deux premiers maillons
            maillon m_sorted = convertirTabMaillon(trierListeMaillons(m), 0);                   // trier cette chaine de maillons
            //printf("occ fg: %d\n", getOccurrence(getFilsGauche(m_sorted), 0));
            return construireArbreDeCodage(m_sorted);                                           // recursivité: rappel fonction
        }
    }
    else
    {
        return NULL;
    }
}

char SUCCESS[8*sizeof(char*)];
void parcoursPrefixe(maillon m, char* binaryCode, int pos, int cote, int c_recherche) {
    //printf("%d : %s\n", pos, binaryCode);
    if (m != NULL)
    {
        binaryCode[pos++] = cote;
        if (getFilsGauche(m) == NULL && getFilsDroit(m) == NULL)
        {
            if (getCaractere(m) == c_recherche)
            {
                binaryCode[pos] = '\0';
                strcpy(SUCCESS, binaryCode); // copier contenu pointeur dans variable globale SUCCESS
            }
        }
        else
        {
            parcoursPrefixe(getFilsGauche(m), binaryCode, pos, 48, c_recherche);
            parcoursPrefixe(getFilsDroit(m), binaryCode, pos, 49, c_recherche);
        }
    }
}

char* creerEnTeteHuffman(maillon liste_triee, maillon ab, char* chaine_entete) {

    if (liste_triee == NULL)
    {
        long int longueur = strlen(chaine_entete);
        chaine_entete[longueur-1] = 9;   // remplacer derniere virgule par: 9 (h_tab)
        chaine_entete[longueur] = 10;    // ajouter signal de fin d'entete: 10 (v_tab)
        chaine_entete[longueur+1] = '\0';
        return chaine_entete;
    }
    else
    {
        // convertir int en char* et concatener les infos voulues dans en-tete
        char* chaine_temp = malloc(1000);
        sprintf(chaine_temp, "%s%d%c%d%c%c", chaine_entete, getCaractere(liste_triee), 9, getOccurrence(liste_triee, 0), 9, '\0'); 
        //                               chaine si presente     caractere en int                occ en int       sep: h_tab
        return creerEnTeteHuffman(getMaillonSuivant(liste_triee), ab, chaine_temp);
    }
}

void creerDocHuffman(maillon liste_triee, maillon arbre, char* fichierChar, char* fileName) {
    char* chaine_entete = malloc(100*strlen(fichierChar)*sizeof(char*));       // on admet: position binaire dans arbre < 100 caracteres + entete
    sprintf(chaine_entete, "%d%c%c", getOccurrence(arbre, 0), 9, '\0');        // convertir somme_occurrence (d'arbre complet) en char* + ajouter ',' + '\0'(signal fin de chaine)
    chaine_entete = creerEnTeteHuffman(liste_triee, arbre, chaine_entete);     // creer entete permettant decompression
    // printf("entete: %s\n", chaine_entete);
    int length_entete = strlen(chaine_entete);                                 // connaitre position fin entete

    // creer nouveau nom (nom fichier compressé)
    char* nouveau_nom = malloc(strlen(fileName)*sizeof(char*));
    strcpy(nouveau_nom, fileName);
    nouveau_nom[strlen(nouveau_nom)-3] = '\0';
    strcat(nouveau_nom, "tar");

    // ecrire en tete dans fichier.bin
    FILE* fichier_compresse = fopen(nouveau_nom, "wb");
    fwrite(chaine_entete, 1, length_entete, fichier_compresse);
    fclose(fichier_compresse);

    // encoder le fichier (fichierChar)
    char* chaine_encodee = malloc(100*strlen(fichierChar)*sizeof(char*));
    chaine_encodee[0] = '\0';

    for(int i=0; i<strlen(fichierChar); ++i)
    {
        char* binCode = malloc(8*sizeof(char*));
        binCode[0] = '\0';
        parcoursPrefixe(arbre, binCode, -1, '\0', fichierChar[i]);  
        strcat(chaine_encodee, SUCCESS);
    }
    // printf("chaine_encodee: %s\n", chaine_encodee); // entete + chaine

    // dans chaine_caracteres: 0 ou 1 codés sur 8 bits (char: 1 octet)
    unsigned char* chaine_compressee = malloc((strlen(chaine_encodee))*sizeof(unsigned char*)); // unsigned: eviter probleme bit de signe
    chaine_compressee[0] = '\0';    // init (fin de) chaine

    int len_tab_int = -1;
    u_int8_t base_dix = 0;
    for(int i=0; i<strlen(chaine_encodee); i+=8)
    {
        len_tab_int++;
        for(int j=0; j<8; ++j)
        {
            // printf("%c", chaine_encodee[i+j]);
            if (chaine_encodee[i+j]!= 0)
            {
                // printf("%c : %d | ", chaine_encodee[i+j], chaine_encodee[i+j]-'0');
                base_dix += (chaine_encodee[i+j]-'0')*pow(2, 7-j);      // 0 ou 1 * 2^j 
                // printf("%c : %d: %d\n", chaine_encodee[i+j], chaine_encodee[i+j]-'0', base_dix);
            }

        }
        // printf("base 10: %d\n", base_dix);
        chaine_compressee[len_tab_int] = base_dix;
        chaine_compressee[len_tab_int+1] = '\0';    // indiquer fin de chaine
        // printf("base 10 dans tableau[%d]: %d\n", len_tab_int, chaine_compressee[len_tab_int]);
        base_dix = 0;
    }

    // for(int i=0; i<len_tab_int+1; ++i)
    // {
    //     printf("%d ", chaine_compressee[i]);
    // } // afficher la chaine -- DEBUG --

    fichier_compresse = fopen(nouveau_nom, "ab+");
    fwrite(chaine_compressee, sizeof(unsigned char), len_tab_int+1, fichier_compresse);
    fclose(fichier_compresse);

    // libérer memoire
    free(chaine_encodee);   
    free(chaine_compressee);
    free(fichierChar);
}

void decompresserDocHuffman(char* fileName) {

    // connaitre taille chaine a decoder et encoder
    FILE* fichier_compresse = fopen(fileName, "rb");
    char* nb_char_doc = malloc(100*sizeof(char*)); // nombre total de caracteres <= 8^100 (largement suffisant)
    nb_char_doc[0] = '\0';

    // permet de connaitre le nombre total d'occurrences, pour le malloc de la chaine
    int current_c = 0;
    int n=0;
    do 
    {
        current_c = fgetc(fichier_compresse);
        nb_char_doc[n] = current_c;
        nb_char_doc[n+1] = '\0';
        n++;
    } while(current_c != 9);

    int nombre_caracteres_malloc = atoi(nb_char_doc); // convertir char* en int | exemple: '100' devient 100
    printf("nombre c pour malloc: %d\n",nombre_caracteres_malloc);

    free(nb_char_doc); // libérer memoire

    // recuperer entete
    long int position_dans_entete = ftell(fichier_compresse);   // connaitre taille entete fichier_compresse
    int taille_entete = 1;
    
    // calculer taille entete
    while(current_c != 10) {                                    // 10: signal de fin d'entete
        current_c = fgetc(fichier_compresse);
        if (current_c == 9)                                     // 9: séparateur dans l'entete
        {
            ++taille_entete;
        }
    }
    printf("taille entete: %d\n", taille_entete);
    fseek(fichier_compresse, position_dans_entete, SEEK_SET);   // revenir au debut du fichier

    // reconstruire arbre
    int char_pos = 0;                                           // position en cours dans la chaine qui retiens le caractere en cours
    char* caractere_en_cours = malloc(3*sizeof(char*));         // codage ascii max: 128 => 3 caracteres (compression ameliorée si un caractere sur un octet au lieu de 3) 
    caractere_en_cours[0] = '\0';
    maillon* m_entete = malloc(((taille_entete/2)+1)*sizeof(maillon));  // definir tableau de maillons destiné a creer arbre
    u_int8_t maillon_pos = 0;
    for(int i=0; i<((taille_entete/2)+1); ++i) {
        m_entete[i] = NULL;
    } // init tableau maillons a NULL

    int pre_maillon[2] = { 0 };                                 // tableau pré-maillon: [caractere, occurrence]
    u_int8_t modul_char = 0;
    do {
        if (current_c == 9)
        {
            int c = atoi(caractere_en_cours);
            if (modul_char%2 == 0)
            {
                pre_maillon[0] = c;                         // retenir caractere en cours d'étude
                printf("%c : ", c);
            }
            else
            {
                pre_maillon[1] = c;                         // retenir occurrence en cours d'étude
                m_entete[maillon_pos] = creerMaillon(pre_maillon[0], pre_maillon[1], -1, NULL, NULL, NULL);   // creer tableau de maillons
                ++maillon_pos;
                printf("%d\n", c);
            }
            
            // re-init chaine
            ++modul_char;                                   // modul_char%2=0 => caractere | sinon => occurrence
            char_pos = 0;
            caractere_en_cours[0] = '\0';
        }
        caractere_en_cours[char_pos] = current_c;           // ajouter le current_c dans la chaine
        caractere_en_cours[char_pos+1] = '\0';              // préciser fin de chaine
        char_pos++;
        current_c = fgetc(fichier_compresse);
    } while(current_c != 10);

    free(caractere_en_cours);   // libérer mémoire

    // for(int i=0; i<(taille_entete/2); ++i)
    // {
    //     printf("car: %c\n", getCaractere(m_entete[i]));
    // } // afficher caracteres entete --- DEBUG ---
    
    maillon m = convertirTabMaillon(m_entete, 0);
    maillon ab = construireArbreDeCodage(m);

    free(m);    // libérer mémoire

    // verifier conformité arbre --- DEBUG ---
    printf("occ premier noeud: %d\n", getOccurrence(ab, 0));
    printf("occ noeud d->g->g: %d", getOccurrence(getFilsGauche(getFilsGauche(getFilsDroit(ab))), 0));
    
    
    // decoder texte
    // convertir en binaire chaque fgetc ==> puis aller a gauche ou a droite dans arbre selon 0 ou 1

    position_dans_entete = ftell(fichier_compresse);
    fseek(fichier_compresse, 0, SEEK_END);                      // position dernier caractere de FILE
    long int last_char = ftell(fichier_compresse);              // connaitre taille fichier_compresse
    fseek(fichier_compresse, position_dans_entete, SEEK_SET);   // revenir a la position retenue

    puts("\nOK 0");

    unsigned char* chaine_compressee = malloc((last_char-position_dans_entete)*sizeof(unsigned char*));     // malloc du nombre caracteres encodés
    chaine_compressee[0] = '\0';                                                                            // init chaine
    puts("OK 1");

    fread(chaine_compressee, (last_char-position_dans_entete), sizeof(unsigned char*), fichier_compresse);   // réécupérer le codage
    puts("OK 2");

    char* chaine_bin = malloc(8*sizeof(chaine_compressee));     // chaque 'caractere' sur 8 bits
    chaine_bin[0] = '\0';                                       // init chaine
    puts("OK 3");

    // printf("%s\n", chaine_compressee);

    for(int i=0; i<(last_char-position_dans_entete); ++i)       // convertir chaine en binaire
    {
        // printf("%d ", chaine_compressee[i]);
        // char* chaine_tmp = malloc(sizeof(chaine_bin));
        // chaine_tmp[0] = '\0';
        // printf("OK 2[%d]\n", i);
        strcat(chaine_bin, convertirIntBinaire(chaine_compressee[i]));

    } // acchicher chaine_compressée -- DEBUG --

    puts("OK 4");

    // printf("\nchaine binaire: %s\n",chaine_bin);
    fclose(fichier_compresse);                                  // fermer le fichier (plus nécessaire à ce moment)
    
    // libérer deux trois trucs
    free(chaine_compressee);

    // decoder la chaine binaire
    char* nouveau_document = malloc(nombre_caracteres_malloc*sizeof(unsigned char*));       // char* contenant le fichier decompressé
    nouveau_document[0] = '\0';                                                             // init chaine

    nouveau_document = parcourirArbre(chaine_bin, nouveau_document, ab, ab, 0, nombre_caracteres_malloc);
    printf("chaine décompressée: %s\n", nouveau_document);
}

char* convertirIntBinaire(int aConvertir) {
    // printf("aConvertir : %d\n", aConvertir);
    char* chaineBinaire = malloc(8*sizeof(char*));      // un octet
    chaineBinaire[0] = '\0';                            // init chaine

    // printf("A convertir: %d\n", aConvertir);

    while(aConvertir>0)
    {
        char* chaine_tmp = malloc(sizeof(chaineBinaire));
        strcpy(chaine_tmp, chaineBinaire);                          // copier dans chaine_tmp pour retenir valeur
        chaineBinaire[0] = '\0';                                    // sprintf concatene toujours dans char* vide
        sprintf(chaineBinaire, "%d%s", (aConvertir%2), chaine_tmp); // ajouter '1' (char) quand 1 (int)
        // chaineBinaire[i] = aConvertir%2;
        aConvertir /= 2;
    }

    while (strlen(chaineBinaire) <= 7)
    {
        char* chaine_tmp = malloc(sizeof(chaineBinaire));
        strcpy(chaine_tmp, chaineBinaire);                          // copier dans chaine_tmp pour retenir valeur
        chaineBinaire[0] = '\0';                                    // sprintf concatene toujours dans char* vide
        sprintf(chaineBinaire, "%d%s", 0, chaine_tmp);              // rajouter les 0 manquants pour atteindre l'octet
        free(chaine_tmp);
    }

    // printf("chaine binaire: %s\n", chaineBinaire);
    return chaineBinaire;
}

char* parcourirArbre(char* chaine_binaire, char* chaine_decomp, maillon ab, maillon ab_temoin, int pos_dans_chaine, int doc_size) {
    if (chaine_binaire[pos_dans_chaine] == '\0')
    {
        return chaine_decomp;
    }
    else
    {
        if (getCaractere(ab) != -1)
        {
            char* chaine_temp = malloc(100*sizeof(char*));                          // sprintf necessite une destination vide
            chaine_temp[0] = '\0';                                                  // init chaine pour sprintf
            // printf("caractere: %c\n", getCaractere(ab));
            sprintf(chaine_temp, "%s%c%c", chaine_decomp, getCaractere(ab), '\0');  // concatener nouveau caractere avec caracteres precedents (+ signal de fin de chaine)
            // printf("chaine: %s\n", chaine_temp);
            return parcourirArbre(chaine_binaire, chaine_temp, ab_temoin, ab_temoin, pos_dans_chaine, doc_size);
        }
        else
        {
            if (chaine_binaire[pos_dans_chaine] == '1')
            {
                // printf("bin: %c\n", chaine_binaire[pos_dans_chaine]);
                return parcourirArbre(chaine_binaire, chaine_decomp, getFilsDroit(ab), ab_temoin, ++pos_dans_chaine, doc_size);
            }
            else
            {
                // printf("bin: %c\n", chaine_binaire[pos_dans_chaine]);
                return parcourirArbre(chaine_binaire, chaine_decomp, getFilsGauche(ab), ab_temoin, ++pos_dans_chaine, doc_size);
            }
        }
    }
}