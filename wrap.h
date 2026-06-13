#ifndef WRAP_H
#define WRAP_H

int     largeur_terminal(void);
void    afficher_avec_wrap(const char *output, const char *prev, int highlight, int largeur);

#endif

