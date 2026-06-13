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
    int     equexit;
    int     no_wrap;
    int     color;
    int     no_color;
    int     follow;
    int     exec_direct;
    char    **cmd;
} t_args;

t_args  parse_args(int argc, char **argv);

#endif
