/*
executor.c
Ce fichier contient la fonction execute_cmd.
Son role est d executer une commande donnee par l utilisateur
comme par exemple : date, ls, ps aux
et de recuperer ce qu elle affiche pour l envoyer a l ecran.
Pour faire ca on utilise :
- pipe  : un tuyau pour recuperer le resultat de la commande
- fork  : pour creer une copie du programme qui va lancer la commande
- execvp: pour lancer la commande dans la copie
- read  : pour lire ce qui sort du tuyau
Auteur : Selihe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"
#include "error.h"

char    *execute_cmd(char **cmd, int *exit_status)
{
    int     tuyau[2];
    int     pid;
    char    morceau[4096];
    char    *resultat;
    int     total;
    int     lu;
    int     statut;

    if (pipe(tuyau) == -1)
    {
        erreur_tuyau();
        return (NULL);
    }

    pid = fork();
    if (pid == -1)
    {
        erreur_processus();
        close(tuyau[0]);
        close(tuyau[1]);
        return (NULL);
    }

    if (pid == 0)
    {
        close(tuyau[0]);
        dup2(tuyau[1], 1);
        dup2(tuyau[1], 2);
        close(tuyau[1]);
        execvp(cmd[0], cmd);
        erreur_commande();
        exit(127);
    }

    close(tuyau[1]);

    resultat = malloc(1);
    if (resultat == NULL)
    {
        erreur_memoire();
        close(tuyau[0]);
        return (NULL);
    }

    resultat[0] = '\0';
    total = 0;

    while ((lu = read(tuyau[0], morceau, 4095)) > 0)
    {
        morceau[lu] = '\0';
        resultat = realloc(resultat, total + lu + 1);
        if (resultat == NULL)
        {
            erreur_memoire();
            close(tuyau[0]);
            return (NULL);
        }
        memcpy(resultat + total, morceau, lu + 1);
        total = total + lu;
    }

    close(tuyau[0]);
    waitpid(pid, &statut, 0);
    *exit_status = WEXITSTATUS(statut);

    if (*exit_status == 127)
    {
        erreur_commande();
        free(resultat);
        return (NULL);
    }

   \ return (resultat);
}
