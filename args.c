#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "args.h"

t_args parse_args(int argc, char **argv) {
    t_args args;
    int opt;

    // 1. Initialisation des valeurs par défaut
    args.interval = 2.0;
    args.highlight = 0;
    args.no_title = 0;
    args.exit_error = 0;

    // 2. Boucle de parsing avec getopt
    while ((opt = getopt(argc, argv, "n:dte")) != -1) {
        switch (opt) {
            case 'n':
                args.interval = atof(optarg); // Convertit la chaîne en double
                break;
            case 'd':
                args.highlight = 1;
                break;
            case 't':
                args.no_title = 1;
                break;
            case 'e':
                args.exit_error = 1;
                break;
            default:
                // Si l'option est inconnue, getopt gère déjà l'affichage de l'erreur
                exit(1); 
        }
    }

    // 3. Vérification : Reste-t-il une commande à exécuter ?
    if (optind >= argc) {
        fprintf(stderr, "Erreur : Aucune commande fournie.\n");
        exit(1);
    }

    // 4. Récupération du pointeur vers la commande restante
    args.cmd = &argv[optind]; 

    return args;
}