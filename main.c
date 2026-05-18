#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "args.h"     // Pour la structure t_args et parse_args
//#include "display.h"  // Pour les fonctions d'affichage 
//#include "executor.h" // Pour l'exécution des commandes 

int main(int argc, char **argv) {
    // 1. Parser les arguments 
    t_args args = parse_args(argc, argv);
    
    printf("[INFO] Options lues. Préparation de la boucle...\n");

    //la partie commentée sera decommentée quand le depot contiendra tous les elements

    /*
    // 2. Initialiser l'affichage ncurses
    display_init();

    // 3. Boucle principale de mywatch
    while (1) {
        int exit_status;
        
        // Exécuter la commande 
        char *output = execute_cmd(args.cmd, &exit_status);
        
        // Afficher l'en-tête (si pas masqué par -t) et le résultat 
        if (!args.no_title) {
            display_header(&args);
        }
        display_output(output, NULL, args.highlight);

        // Libérer la mémoire allouée pour la sortie de la commande
        free(output);

        // 4. Attendre l'intervalle spécifié (converti en microsecondes)
        usleep((useconds_t)(args.interval * 1000000)); 
        
        // INTERRUPTEUR DE TEST : Permet d'éviter la boucle infinie 
        // pendant que nous testons avec nos fichiers simulés (stubs)
        break; 
    }

    // 5. Nettoyer et fermer ncurses proprement
    display_cleanup();
    */

    return 0;
}