#ifndef ARGS_H
#define ARGS_H

typedef struct s_args
{
    double  interval;
    int     highlight;
    int     no_title;
    int     exit_error;
    int     chgexit;
    int     beep;
    int     precise;
    char    **cmd;
} t_args;

t_args  parse_args(int argc, char **argv);

#endif
