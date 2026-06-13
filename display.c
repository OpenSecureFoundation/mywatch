/*
** display.c
**
** Ce fichier affiche le resultat de la commande
** a l ecran avec l en tete et le rafraichissement
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "display.h"
#include "color.h"
#include "wrap.h"

static void afficher_entete(t_args *args)
{
    time_t  t;
    char    *heure;
    int     i;

    t = time(NULL);
    heure = ctime(&t);
    heure[strlen(heure) - 1] = '\0';
    printf("Every %.1fs: ", args->interval);
    i = 0;
    while (args->cmd[i])
    {
        printf("%s ", args->cmd[i]);
        i++;
    }
    printf("\t%s\n\n", heure);
}

void    display_screen(t_args *args, const char *output, const char *prev)
{
    size_t  i;
    int     largeur;
    char    *texte_affiche;
    int     a_liberer;

    if (!args->follow)
        printf("\033[2J\033[H");

    if (!args->no_title)
        afficher_entete(args);

    texte_affiche = (char *)output;
    a_liberer = 0;

    if (args->no_color)
    {
        texte_affiche = enlever_couleurs(output);
        if (texte_affiche == NULL)
            texte_affiche = (char *)output;
        else
            a_liberer = 1;
    }

    if (args->no_wrap)
    {
        largeur = largeur_terminal();
        afficher_avec_wrap(texte_affiche, prev, args->highlight, largeur);
    }
    else if (!args->highlight || !prev)
    {
        printf("%s", texte_affiche);
    }
    else
    {
        i = 0;
        while (i < strlen(texte_affiche))
        {
            if (i >= strlen(prev) || texte_affiche[i] != prev[i])
                printf("\033[7m%c\033[0m", texte_affiche[i]);
            else
                printf("%c", texte_affiche[i]);
            i++;
        }
    }

    if (args->follow)
        printf("\n---\n");

    if (a_liberer)
        free(texte_affiche);
}
