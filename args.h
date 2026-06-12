


#ifndef ARGS_H
#define ARGS_H

typedef struct s_args {

    double  interval;    // Option -n 
    int     beep;        // Option -b 
    int     color_mode;  // Options -c / -C : 
    char    **cmd;       // Le tableau d'arguments pour execvp 
    char    *command;    // La chaîne  pour l'affichage du titre 
      int     no_title;    // Option -t :
    int     highlight;   //option -d 
    int     exit_error;  // Option -e
    int     chgexit;     // Option -g 
    int     precise;     // Option -p 

    
} t_args;

// Déclaration de la fonction de segmentation de la commande entrée par le user
t_args parse_args(int argc, char **argv);

#endif