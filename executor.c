/*
** executor.c
**
** Execute une commande et recupere son resultat
**
** syscall 0  = read, 3 = close, 22 = pipe
** syscall 33 = dup2, 57 = fork, 59 = execve, 61 = waitpid
**
** Auteur : Selihe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include "executor.h"
#include "error.h"
#include "shell.h"

static char *chercher_commande(char *nom)
{
    char    *dossiers[] = {"/usr/bin/", "/bin/", "/usr/local/bin/", NULL};
    char    *chemin;
    int     i;
    long    fd;

    if (nom[0] == '/')
        return (nom);

    i = 0;
    while (dossiers[i] != NULL)
    {
        chemin = malloc(strlen(dossiers[i]) + strlen(nom) + 1);
        if (chemin == NULL)
            return (NULL);
        strcpy(chemin, dossiers[i]);
        strcat(chemin, nom);
        fd = syscall(2, chemin, 0, 0);
        if (fd != -1)
        {
            syscall(3, fd);
            return (chemin);
        }
        free(chemin);
        i++;
    }
    return (NULL);
}

static void lancer_commande(char **cmd, int exec_direct)
{
    char    *chemin;
    char    *chaine_cmd;
    char    *argv_shell[4];

    if (exec_direct)
    {
        chemin = chercher_commande(cmd[0]);
        if (chemin == NULL)
        {
            erreur_commande();
            exit(127);
        }
        syscall(59, chemin, cmd, NULL);
    }
    else
    {
        chaine_cmd = construire_chaine(cmd);
        if (chaine_cmd == NULL)
        {
            erreur_memoire();
            exit(127);
        }
        argv_shell[0] = "/bin/sh";
        argv_shell[1] = "-c";
        argv_shell[2] = chaine_cmd;
        argv_shell[3] = NULL;
        syscall(59, "/bin/sh", argv_shell, NULL);
    }
    erreur_commande();
    exit(127);
}

char    *execute_cmd(char **cmd, int *exit_status, int exec_direct)
{
    int     tuyau[2];
    long    pid;
    char    morceau[4096];
    char    *resultat;
    int     total;
    long    lu;
    int     statut;

    if (syscall(22, tuyau) == -1)
    {
        erreur_tuyau();
        return (NULL);
    }

    pid = syscall(57);
    if (pid == -1)
    {
        erreur_processus();
        syscall(3, tuyau[0]);
        syscall(3, tuyau[1]);
        return (NULL);
    }

    if (pid == 0)
    {
        syscall(3, tuyau[0]);
        syscall(33, tuyau[1], 1);
        syscall(33, tuyau[1], 2);
        syscall(3, tuyau[1]);
        lancer_commande(cmd, exec_direct);
    }

    syscall(3, tuyau[1]);

    resultat = malloc(1);
    if (resultat == NULL)
    {
        erreur_memoire();
        syscall(3, tuyau[0]);
        return (NULL);
    }
    resultat[0] = '\0';
    total = 0;

    while ((lu = syscall(0, tuyau[0], morceau, 4095)) > 0)
    {
        morceau[lu] = '\0';
        resultat = realloc(resultat, total + lu + 1);
        if (resultat == NULL)
        {
            erreur_memoire();
            syscall(3, tuyau[0]);
            return (NULL);
        }
        memcpy(resultat + total, morceau, lu + 1);
        total = total + lu;
    }

    syscall(3, tuyau[0]);
    syscall(61, pid, &statut, 0);
    *exit_status = WEXITSTATUS(statut);

    if (*exit_status == 127)
    {
        erreur_commande();
        free(resultat);
        return (NULL);
    }
    return (resultat);
}
