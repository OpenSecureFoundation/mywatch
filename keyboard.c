/*
** keyboard.c
**
** Ce fichier permet de lire le clavier sans bloquer
** le programme, pour detecter les touches :
** - q       : quitter
** - espace  : relancer immediatement
**
** syscall 0  = read
** syscall 16 = ioctl (pour changer le mode terminal)
** syscall 23 = select
**
** Auteur : Tsafac et Selihe
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/syscall.h>
#include <sys/select.h>
#include "keyboard.h"

#define TCGETS 0x5401
#define TCSETS 0x5402

static struct termios ancien_mode;

void    set_mode_clavier(void)
{
    struct termios nouveau_mode;

    /* recuperer la config actuelle du terminal */
    syscall(16, 0, TCGETS, &ancien_mode);

    nouveau_mode = ancien_mode;

    /* on enleve le mode canonique et l affichage des touches */
    nouveau_mode.c_lflag &= ~(ICANON | ECHO);

    /* appliquer la nouvelle config */
    syscall(16, 0, TCSETS, &nouveau_mode);
}

void    restore_mode_clavier(void)
{
    syscall(16, 0, TCSETS, &ancien_mode);
}

int     touche_appuyee(void)
{
    struct timeval tv;
    fd_set         fds;

    tv.tv_sec  = 0;
    tv.tv_usec = 0;

    FD_ZERO(&fds);
    FD_SET(0, &fds);

    return (syscall(23, 1, &fds, NULL, NULL, &tv) > 0);
}

char    lire_touche(void)
{
    char    c;

    syscall(0, 0, &c, 1);
    return (c);
}
