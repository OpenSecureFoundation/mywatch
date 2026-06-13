/*
** shell.c
**
** Construit une seule chaine a partir d un tableau
** de mots, pour pouvoir la passer a sh -c (pour -x)
**
** Auteur : Selihe
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"

char    *construire_chaine(char **cmd)
{
    int     i;
    int     total;
    char    *chaine;

    total = 0;
    i = 0;
    while (cmd[i] != NULL)
    {
        total = total + (int)strlen(cmd[i]) + 1;
        i++;
    }

    chaine = malloc(total + 1);
    if (chaine == NULL)
        return (NULL);

    chaine[0] = '\0';
    i = 0;
    while (cmd[i] != NULL)
    {
        strcat(chaine, cmd[i]);
        if (cmd[i + 1] != NULL)
            strcat(chaine, " ");
        i++;
    }
    return (chaine);
}
