#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "args.h" 
#include "executor.h"
#include "display.h"
#include "utils.h"
#include "help.h"

//  fonction pour enlever les couleurs ANSI si l'option -C est active
void strip_ansi_colors(char *str) {
    if (!str) return;
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src == '\033' && *(src + 1) == '[') {
            src += 2;
            while (*src && *src != 'm') {
                src++;
            }
            if (*src == 'm') src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

int main(int argc, char **argv) {
    // Vérification de l'aide
    if (argc >= 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        afficher_help();
        return 0;
    }

    //  Analyse manuelle de la ligne de commande 
    t_args args = parse_args(argc, argv); 

    // Reconstitution de la commande  pour l'en-tête
    static char commande_complete[512] = "";
    int i = 0;
    while (args.cmd[i] != NULL) {
        strcat(commande_complete, args.cmd[i]);
        strcat(commande_complete, " ");
        i++;
    }
    args.command = commande_complete;

    char *current_output = NULL;
    char *previous_output = NULL;

    //  Configuration des signaux (Ctrl+C)
    setup_signals(); 

    // Initialisation de l'écran alternatif
    display_init(); 

    // Boucle de surveillance principale
    while(1) {
        int exit_status = 0;
        
        // Exécution de la commande système
        current_output = execute_cmd(args.cmd, &exit_status); 
        
        // Option -b : Bip sonore si la commande échoue 
        if (args.beep && exit_status != 0) {
            printf("\a");
            fflush(stdout);
        }

        // Option -C : Suppression des couleurs ANSI si l'utilisateur l'a demandé
        if (args.color_mode == 0) {
            strip_ansi_colors(current_output);
        }

        // Option -e : Quitter immédiatement si la commande échoue
        if (args.exit_error && exit_status != 0) {
            if (current_output) free(current_output);
            break; 
        }

        // Affichage de l'en-tête graphique
        if (!args.no_title) {
            display_header(&args);
        } else {
            printf("\033[2J\033[H"); 
        }
        
        // Affichage du texte avec surlignage des changements
        display_output(current_output, previous_output, args.highlight);

        // Option -g : Quitter si l'output a changé par rapport au tour précédent
        if (args.chgexit && previous_output != NULL && strcmp(current_output, previous_output) != 0) {
            if (current_output) free(current_output);
            break;
        }

        // Sauvegarde de l'historique pour le prochain cycle
        if (previous_output) {
            free(previous_output);
        }
        previous_output = current_output;
        
        // 7. Attente et écoute active du clavier ('q' pour quitter, 'Espace' pour forcer)
        double temps_ecoule = 0;
        int force_refresh = 0;
        
        while (temps_ecoule < args.interval && !force_refresh) {
            int key = check_keyboard(); // Appelle la fonction de Gregory dans utils.c
            if (key == 1) { 
                display_cleanup();
                if (previous_output) free(previous_output);
                return 0;
            }
            if (key == 2) { 
                force_refresh = 1; 
            }
            usleep(50000); // Pause de 50ms pour ne pas surcharger le CPU
            if (!force_refresh) {
                temps_ecoule += 0.05;
            }
        }
    }
    
    // 8. Nettoyage final avant de quitter proprement
    display_cleanup();
    if (previous_output) free(previous_output);

    return 0;
}