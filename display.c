/*
** display.c
**
** Ce fichier affiche le resultat de la commande
** a l ecran avec l en tete et le rafraichissement
**
** syscall 16 = ioctl (pour recuperer la taille du terminal)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "display.h"

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

static int largeur_terminal(void)
{
    struct winsize ws;

    if (syscall(16, 1, TIOCGWINSZ, &ws) == -1)
        return (80);
    if (ws.ws_col == 0)
        return (80);
    return (ws.ws_col);
}

/* enleve les codes couleur ANSI du texte (pour -C) */
static char *enlever_couleurs(const char *texte)
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

static void afficher_avec_wrap(const char *output, const char *prev, int highlight, int largeur)
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

void    display_screen(t_args *args, const char *output, const char *prev)
{
    size_t  i;
    int     largeur;
    char    *texte_affiche;
    int     a_liberer;

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

    if (a_liberer)
        free(texte_affiche);
}
