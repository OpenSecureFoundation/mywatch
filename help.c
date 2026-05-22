/*
** help.c
**
** Ce fichier affiche l aide de mywatch2
** quand l utilisateur tape --help
**
** Auteur : Selihe
*/

#include <stdio.h>
#include "help.h"

void    afficher_help(void)
{
    printf("\nUTILISATION :\n");
    printf("    ./mywatch2 [options] commande\n");
    printf("\nOPTIONS :\n");
    printf("    -n <secondes>   Intervalle de rafraichissement (defaut: 2)\n");
    printf("    -d              Surligner les differences\n");
    printf("    -t              Masquer l en tete\n");
    printf("    -e              Quitter si erreur\n");
    printf("\nEXEMPLES :\n");
    printf("    ./mywatch2 date\n");
    printf("    ./mywatch2 -n 1 date\n");
    printf("    ./mywatch2 -d ls\n");
    printf("    ./mywatch2 -n 5 -d df -h\n");
    printf("\nAUTEURS :\n");
    printf("    Belvira, Christelle, Selihe, Gregory\n\n");
}
