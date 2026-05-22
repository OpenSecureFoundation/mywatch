/*
error.c
Ce fichier gere tous les messages d erreur
du programme mywatch2.
Les erreurs s affichent en rouge.
Auteur : Selihe
*/

#include <stdio.h>
#include "error.h"

void    afficher_erreur(char *message)
{
    printf("\033[31m ERREUR : %s \033[0m\n", message);
}

void    erreur_tuyau(void)
{
    afficher_erreur("impossible de creer le tuyau");
}

void    erreur_processus(void)
{
    afficher_erreur("impossible de creer le processus");
}

void    erreur_memoire(void)
{
    afficher_erreur("memoire insuffisante");
}

void    erreur_commande(void)
{
    afficher_erreur("commande introuvable");
}
