/*
** color.c
**
** Ce fichier contient la fonction qui enleve
** les codes couleur ANSI d un texte (pour -C)
**
** Auteur : Selihe
*/

#include <stdlib.h>
#include <string.h>
#include "color.h"

char    *enlever_couleurs(const char *texte)
{
    char    *propre;
    size_t  i;
    size_t  j;

    propre = malloc(strlen(texte) + 1);
    if (propre == NULL)
        return (NULL);

    i = 0;
    j = 0;
    while (texte[i] != '\0')
    {
        if (texte[i] == '\033' && texte[i + 1] == '[')
        {
            i = i + 2;
            while (texte[i] != '\0' &&
                   !((texte[i] >= 'a' && texte[i] <= 'z') ||
                     (texte[i] >= 'A' && texte[i] <= 'Z')))
                i++;
            if (texte[i] != '\0')
                i++;
        }
        else
        {
            propre[j] = texte[i];
            j++;
            i++;
        }
    }
    propre[j] = '\0';
    return (propre);
}

