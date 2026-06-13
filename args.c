#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "help.h"

t_args  parse_args(int argc, char **argv)
{
    t_args  args;
    int     i;

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

    args.interval   = 2.0;
    args.highlight  = 0;
    args.no_title   = 0;
    args.exit_error = 0;
    args.chgexit    = 0;
    args.beep       = 0;
    args.precise    = 0;
    args.cmd        = NULL;

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
