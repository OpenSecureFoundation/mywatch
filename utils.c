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
#include <unistd.h>     
#include <sys/select.h> 
#include <termios.h>    
#include <sys/syscall.h> // Indispensable pour utiliser syscall()


/* static void quitter(int sig)
{
    (void)sig;
    printf("\033[2J\033[H");
    printf("\n");
    exit(0);
} */

void display_cleanup(void);

static void quitter(int sig)
{
    (void)sig;
    display_cleanup(); // Remet le terminal au propre et réaffiche le curseur !
    printf("\n[MyWatch] Surveillance interrompue.\n");
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



int check_keyboard(void) {
    struct timeval tv = {0, 0}; 
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    
    // On surveille le clavier
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    
    if (FD_ISSET(STDIN_FILENO, &fds)) {
        char c;
        // Remplacement par syscall(0) comme exigé par le prof !
        if (syscall(0, STDIN_FILENO, &c, 1) > 0) {
            if (c == 'q' || c == 'Q') return 1; 
            if (c == ' ') return 2;             
        }
    }
    return 0; 
}