#ifndef ARGS_H
#define ARGS_H

typedef struct s_args {
    double interval;
    int highlight;
    int no_title;
    int exit_error;
    char **cmd;       // Tableau de chaînes pour la commande découpée
} t_args;

// Les prototypes indispensables pour le main.c
t_args init_args(void);
void split_command(t_args *args, char *commande_saisie);

#endif