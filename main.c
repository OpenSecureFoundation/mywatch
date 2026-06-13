#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "args.h"
#include "executor.h"
#include "display.h"
#include "utils.h"
#include "keyboard.h"

int main(int argc, char **argv)
{
    t_args  args;
    char    *resultat;
    char    *precedent;
    int     statut;
    time_t  debut;
    time_t  fin;
    double  duree;
    double  attente;
    char    touche;
    int     sauter_attente;
    int     compteur_identique;
    int     code_sortie;

    args      = parse_args(argc, argv);
    precedent = NULL;
    statut    = 0;
    compteur_identique = 0;
    code_sortie = 0;

    setup_signals();
    set_mode_clavier();

    while (1)
    {
        debut = time(NULL);

        resultat = execute_cmd(args.cmd, &statut, args.exec_direct);

        if (resultat == NULL)
        {
            printf("\033[31m Arret du programme. \033[0m\n");
            code_sortie = 2;
            break ;
        }

        if (args.beep && statut != 0)
            printf("\a");

        if (args.exit_error && statut != 0)
        {
            free(resultat);
            if (precedent)
                free(precedent);
            code_sortie = statut;
            break ;
        }

        display_screen(&args, resultat, precedent);

        if (args.chgexit && precedent != NULL)
        {
            if (strcmp(resultat, precedent) != 0)
            {
                free(resultat);
                free(precedent);
                precedent = NULL;
                code_sortie = 0;
                break ;
            }
        }

        if (args.equexit && precedent != NULL)
        {
            if (strcmp(resultat, precedent) == 0)
                compteur_identique++;
            else
                compteur_identique = 0;

            if (compteur_identique >= args.equexit)
            {
                free(resultat);
                free(precedent);
                precedent = NULL;
                code_sortie = 0;
                break ;
            }
        }

        if (precedent)
            free(precedent);
        precedent = resultat;

        fin = time(NULL);
        duree = (double)(fin - debut);

        if (args.precise)
            attente = args.interval - duree;
        else
            attente = args.interval;

        if (attente <= 0)
            attente = 0;

        sauter_attente = 0;
        while (attente > 0 && !sauter_attente)
        {
            if (touche_appuyee())
            {
                touche = lire_touche();

                if (touche == 'q')
                {
                    restore_mode_clavier();
                    if (precedent)
                        free(precedent);
                    printf("\nAu revoir !\n");
                    return (0);
                }
                if (touche == ' ')
                    sauter_attente = 1;
            }

            if (!sauter_attente)
            {
                precise_sleep(0.1);
                attente = attente - 0.1;
            }
        }
    }

    restore_mode_clavier();

    if (precedent)
        free(precedent);

    return (code_sortie);
}
