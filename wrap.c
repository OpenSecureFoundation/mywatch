/*
** wrap.c
**
** Ce fichier gere l affichage avec coupure de ligne
** a la largeur du terminal (pour -w)
**
** syscall 16 = ioctl (pour recuperer la taille du terminal)
**
** Auteur : Selihe
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include "wrap.h"

int     largeur_terminal(void)
{
    struct winsize ws;

    if (syscall(16, 1, TIOCGWINSZ, &ws) == -1)
        return (80);
    if (ws.ws_col == 0)
        return (80);
    return (ws.ws_col);
}

void    afficher_avec_wrap(const char *output, const char *prev, int highlight, int largeur)
{
    size_t  i;
    size_t  col;

    i   = 0;
    col = 0;

    while (i < strlen(output))
    {
        if (output[i] == '\n')
        {
            printf("\n");
            col = 0;
            i++;
            continue ;
        }

        if (col < (size_t)largeur)
        {
            if (highlight && prev && i < strlen(prev) && output[i] != prev[i])
                printf("\033[7m%c\033[0m", output[i]);
            else
                printf("%c", output[i]);
            col++;
        }
        else
        {
            while (i < strlen(output) && output[i] != '\n')
                i++;
            continue ;
        }
        i++;
    }
}
