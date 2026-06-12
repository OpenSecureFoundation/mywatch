#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "args.h"

t_args parse_args(int argc, char **argv) {
    t_args args;
    int i = 1;

    // Initialisation de TOUTES les valeurs par défaut
    args.interval = 2.0;   
    args.highlight = 0;  
    args.no_title = 0;   
    args.exit_error = 0; 
    args.beep = 0;       
    args.color_mode = 1; 
    args.chgexit = 0;    
    args.precise = 0;    
    args.cmd = NULL;
    args.command = NULL;

    // Boucle d'analyse manuelle des arguments
    while (i < argc && argv[i][0] == '-') {
        // Option -n 
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                args.interval = atof(argv[i + 1]);
                if (args.interval <= 0) {
                    fprintf(stderr, "Erreur : L'intervalle doit être supérieur à 0.\n"); 
                    exit(1);
                }
                i += 2;
            } else {
                fprintf(stderr, "Erreur : L'option -n nécessite une valeur.\n"); 
                exit(1);
            }
        }
        // Option -d 
        else if (strcmp(argv[i], "-d") == 0) {
            args.highlight = 1;
            i++;
        }
        // Option -t 
        else if (strcmp(argv[i], "-t") == 0) {
            args.no_title = 1;
            i++;
        }
        // Option -e 
        else if (strcmp(argv[i], "-e") == 0) {
            args.exit_error = 1;
            i++;
        }
        // Option -b 
        else if (strcmp(argv[i], "-b") == 0) {
            args.beep = 1;
            i++;
        }
        // Option -c 
        else if (strcmp(argv[i], "-c") == 0) {
            args.color_mode = 1;
            i++;
        }
        // Option -C 
        else if (strcmp(argv[i], "-C") == 0) {
            args.color_mode = 0;
            i++;
        }

        // Option -g 
        else if (strcmp(argv[i], "-g") == 0) {
            args.chgexit = 1;
            i++;
        }
        // Option -p 
        else if (strcmp(argv[i], "-p") == 0) {
            args.precise = 1;
            i++;
        }
        // Si l'option n'existe pas
        else {
            fprintf(stderr, "Erreur : Option inconnue '%s'.\n", argv[i]); 
            exit(1);
        }
    }

    if (i >= argc) {
        fprintf(stderr, "Erreur : Aucune commande fournie.\n"); 
        exit(1);
    }

    args.cmd = &argv[i]; 
    return args;
}