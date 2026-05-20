#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "args.h" 

int main() {
    // 1. Initialisation avec les valeurs par défaut de args.c
    t_args args = init_args(); 

    int choix = 0;
    char commande_saisie[256];

    printf("==================================================\n");
    printf("    BIENVENUE DANS VOTRE ASSISTANT MYWATCH        \n");
    printf("==================================================\n\n");

    // 2. Menu interactif pour les options
    do {
        printf("Configuration actuelle :\n");
        printf("  1. Modifier l'intervalle de temps (Actuel : %.1fs)\n", args.interval);
        printf("  2. Surligner les changements (Actuel : %s)\n", args.highlight ? "OUI" : "NON");
        printf("  3. Masquer l'en-tête/titre (Actuel : %s)\n", args.no_title ? "OUI" : "NON");
        printf("  4. Quitter si la commande échoue (Actuel : %s)\n", args.exit_error ? "OUI" : "NON");
        printf("  5. Valider les options et passer à la commande\n");
        printf("\nVotre choix (1-5) : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide !\n");
            return 1;
        }
        
        // Vider le tampon de saisie
        while (getchar() != '\n');

        switch(choix) {
            case 1:
                printf("Entrez le nouvel intervalle en secondes (ex: 1.5) : ");
                if (scanf("%lf", &args.interval) != 1) args.interval = 2.0;
                while (getchar() != '\n'); // Re-vider après le scanf
                break;
            case 2:
                args.highlight = !args.highlight;
                break;
            case 3:
                args.no_title = !args.no_title;
                break;
            case 4:
                args.exit_error = !args.exit_error;
                break;
            case 5:
                printf("\nOptions configurées avec succès !\n");
                break;
            default:
                printf("Option inconnue, réessayez.\n");
        }
        printf("\n--------------------------------------------------\n");
    } while (choix != 5);

    // 3. Demande de la commande à exécuter
    printf("\nEntrez la commande dont vous souhaitez voir l'évolution (ex: ls -l) :\n");
    printf("> ");
    if (fgets(commande_saisie, sizeof(commande_saisie), stdin) != NULL) {
        commande_saisie[strcspn(commande_saisie, "\n")] = 0; // Enlever le '\n'
    }

    // 4. Appel de ta fonction de découpage
    split_command(&args, commande_saisie);

    // ============================================================
    // ZONE DE TEST : On vérifie si ton code a bien tout enregistré
    // ============================================================
    printf("\n================ VERIFICATION ================\n");
    printf("Intervalle choisi : %.1fs\n", args.interval);
    printf("Mode Diff (-d)    : %s\n", args.highlight ? "Activé" : "Désactivé");
    printf("Masquer Titre (-t): %s\n", args.no_title ? "Oui" : "Non");
    printf("Quitter Erreur (-e): %s\n", args.exit_error ? "Oui" : "Non");
    
    printf("Tableau de commande découpé (args.cmd) :\n");
    int i = 0;
    while (args.cmd[i] != NULL) {
        printf("  -> args.cmd[%d] = \"%s\"\n", i, args.cmd[i]);
        i++;
    }
    printf("==============================================\n");

    // Libération de la mémoire de test
    free(args.cmd);

    return 0;
}