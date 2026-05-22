#include <stdio.h>
#include <string.h>
#include <time.h>
#include "display.h"

/* --- Séquences ANSI utiles ---
 * \033[2J\033[H  : effacer l'écran et revenir en haut à gauche
 * \033[7m...\033[0m : inverser les couleurs pour le highlight
 * \033[?1049h    : activer l'écran alternatif (comme le vrai watch)
 * \033[?1049l    : désactiver l'écran alternatif
 */

void display_init(void)
{
    // Activer l'écran alternatif
    printf("\033[?1049h");
    // Cacher le curseur
    printf("\033[?25l");
    fflush(stdout);
}

void display_header(t_args *args)
{
    time_t      now;
    struct tm   *tm_info;
    char        time_str[64];

    // Obtenir l'heure actuelle
    time(&now);
    tm_info = localtime(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    // Effacer l'écran et revenir en haut
    printf("\033[2J\033[H");

    // Ligne 1 : Every Xs: commande     heure
    printf("Every %ds: %-40s %s\n\n", args->interval, args->command, time_str);
    fflush(stdout);
}

void display_output(const char *current, const char *previous, int highlight)
{
    int i;
    int len_cur;
    int len_prev;

    if (!current)
        return;

    len_cur  = strlen(current);
    len_prev = (previous) ? strlen(previous) : 0;

    for (i = 0; i < len_cur; i++)
    {
        // Si highlight actif ET le caractère a changé par rapport à previous
        if (highlight && previous && i < len_prev && current[i] != previous[i])
        {
            // Couleurs inversées pour signaler le changement
            printf("\033[7m%c\033[0m", current[i]);
        }
        else
        {
            putchar(current[i]);
        }
    }
    fflush(stdout);
}

void display_cleanup(void)
{
    // Réafficher le curseur
    printf("\033[?25h");
    // Désactiver l'écran alternatif → retour au terminal normal
    printf("\033[?1049l");
    fflush(stdout);
}