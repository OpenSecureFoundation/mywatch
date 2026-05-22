/*
** utils.h
**
** Ce fichier contient les outils utiles
** pour tout le programme :
** - attendre entre chaque rafraichissement
** - gerer le Ctrl+C pour quitter proprement
*/

#ifndef UTILS_H
#define UTILS_H

void    precise_sleep(double secondes);
void    setup_signals(void);

#endif
