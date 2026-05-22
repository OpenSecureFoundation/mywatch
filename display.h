#ifndef DISPLAY_H
#define DISPLAY_H

#include "args.h"



/* Initialiser le terminal pour l'affichage plein écran */
void display_init(void);

/* Afficher l'en-tete : intervalle, commande, heure actuelle */
void display_header(t_args *args);

/* Afficher le contenu, avec highlight si -d est actif */
void display_output(const char *current, const char *previous, int highlight);

/* Restaurer le terminal a son etat normal (appele en fin de programme) */
void display_cleanup(void);

#endif