#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "help.h"

t_args  parse_args(int argc, char **argv)
{
    t_args  args;
    int     i;
    char    *env_interval;

    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        afficher_help();
        exit(0);
    }

    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
    {
        printf("mywatch2 version 1.0\n");
        exit(0);
    }

    args.interval = 2.0;

    env_interval = getenv("WATCH_INTERVAL");
    if (env_interval != NULL)
    {
        args.interval = atof(env_interval);
        if (args.interval <= 0)
            args.interval = 2.0;
    }

    args.highlight   = 0;
    args.no_title    = 0;
    args.exit_error  = 0;
    args.chgexit     = 0;
    args.beep        = 0;
    args.precise     = 0;
    args.equexit     = 0;
    args.no_wrap     = 0;
    args.color       = 0;
    args.no_color    = 0;
    args.follow      = 0;
    args.exec_direct = 0;
    args.cmd         = NULL;

    i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "ERREUR : -n necessite une valeur\n");
                exit(1);
            }
            i++;
            args.interval = atof(argv[i]);
            if (args.interval <= 0)
                args.interval = 2.0;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "ERREUR : -q necessite une valeur\n");
                exit(1);
            }
            i++;
            args.equexit = atoi(argv[i]);
            if (args.equexit <= 0)
            {
                fprintf(stderr, "ERREUR : -q doit etre superieur a 0\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-d") == 0)
            args.highlight = 1;
        else if (strcmp(argv[i], "-t") == 0)
            args.no_title = 1;
        else if (strcmp(argv[i], "-e") == 0)
            args.exit_error = 1;
        else if (strcmp(argv[i], "-g") == 0)
            args.chgexit = 1;
        else if (strcmp(argv[i], "-b") == 0)
            args.beep = 1;
        else if (strcmp(argv[i], "-p") == 0)
            args.precise = 1;
        else if (strcmp(argv[i], "-w") == 0)
            args.no_wrap = 1;
        else if (strcmp(argv[i], "-c") == 0)
            args.color = 1;
        else if (strcmp(argv[i], "-C") == 0)
            args.no_color = 1;
        else if (strcmp(argv[i], "-f") == 0)
            args.follow = 1;
        else if (strcmp(argv[i], "-x") == 0)
            args.exec_direct = 1;
        else
        {
            fprintf(stderr, "ERREUR : option inconnue\n");
            exit(1);
        }
        i++;
    }

    if (i >= argc)
    {
        fprintf(stderr, "Usage: ./mywatch2 [-n sec] [-d] [-t] [-e] commande\n");
        exit(1);
    }

    args.cmd = &argv[i];
    return (args);
}
