/*
** screenshot.c
**
** Sauvegarde le contenu actuel dans un fichier texte
**
** syscall 2  = open
** syscall 1  = write
** syscall 3  = close
**
** Auteur : Selihe
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "screenshot.h"

void    prendre_screenshot(const char *contenu)
{
    char    nom[64];
    time_t  t;
    long    fd;

    t = time(NULL);
    strftime(nom, sizeof(nom), "screenshot_%Y-%m-%d_%H-%M-%S.txt", localtime(&t));

    fd = syscall(2, nom, 577, 0644);
    if (fd == -1)
    {
        printf("ERREUR : impossible de creer le screenshot\n");
        return ;
    }

    syscall(1, fd, contenu, strlen(contenu));
    syscall(3, fd);

    printf("\nScreenshot sauvegarde : %s\n", nom);
}
