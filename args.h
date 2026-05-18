#ifndef ARGS_H
#define ARGS_H

/* Structure pour stocker les options du projet mywatch */
typedef struct s_args {
    double  interval;    /* -n : intervalle en secondes, defaut 2.0 */
    int     highlight;   /* -d : activer le highlight des differences */
    int     no_title;    /* -t : desactiver l'en-tete */
    int     exit_error;  /* -e : quitter en cas d'erreur */
    char    **cmd;       /* la commande a executer (argv restant) */
} t_args;

/* Prototype de ta fonction de parsing */
t_args  parse_args(int argc, char **argv);

#endif