#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "args.h"

// 1. Fonction qui initialise les arguments avec les valeurs par défaut
t_args init_args(void) {
    t_args args;
    
    args.interval = 2.0;
    args.highlight = 0;
    args.no_title = 0;
    args.exit_error = 0;
    args.cmd = NULL; // Pas encore de commande au départ
    
    return args;
}

// 2. Fonction qui découpe la chaîne de l'utilisateur en tableau de mots (pour Selihe)
void split_command(t_args *args, char *commande_saisie) {
    // On alloue dynamiquement de l'espace pour le tableau de pointeurs (ex: max 64 arguments)
    args->cmd = malloc(64 * sizeof(char*));
    if (args->cmd == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(1);
    }

    int i = 0;
    // strtok découpe la chaîne à chaque espace ' '
    char *token = strtok(commande_saisie, " ");
    
    while (token != NULL && i < 63) {
        args->cmd[i] = token; // On stocke le morceau (ex: "ls", puis "-l")
        i++;
        token = strtok(NULL, " ");
    }
    
    args->cmd[i] = NULL; // Git/Linux ont toujours besoin que le tableau se termine par NULL
}