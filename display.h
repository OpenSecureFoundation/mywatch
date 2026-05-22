#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct s_args {
    int     interval;      // intervalle en secondes
    int     highlight;     // flag -d activé ou non
    char    *command;      // la commande à exécuter
} t_args;

/* Initialiser le terminal pour l'affichage plein écran */
void display_init(void);

/* Afficher l'en-tete : intervalle, commande, heure actuelle */
void display_header(t_args *args);

/* Afficher le contenu, avec highlight si -d est actif */
void display_output(const char *current, const char *previous, int highlight);

/* Restaurer le terminal a son etat normal (appele en fin de programme) */
void display_cleanup(void);

#endif