/*
** utils.c
**
** Ce fichier contient deux fonctions utiles :
** - precise_sleep : attend un certain nombre de secondes
** - setup_signals : gere le Ctrl+C pour quitter proprement
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "utils.h"

static void quitter(int sig)
{
    (void)sig;
    printf("\033[2J\033[H");
    printf("\n");
    exit(0);
}

void    setup_signals(void)
{
    signal(SIGINT, quitter);
}

void    precise_sleep(double secondes)
{
    struct timespec temps;

    temps.tv_sec  = (time_t)secondes;
    temps.tv_nsec = (long)((secondes - (double)temps.tv_sec) * 1000000000);
    nanosleep(&temps, NULL);
}
