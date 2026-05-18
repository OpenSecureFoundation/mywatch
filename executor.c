#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"

/*
 executor.c
 Ce fichier contient la fonction execute_cmd.
 Son role est d executer une commande donnee par l utilisateur
 comme par exemple : date, ls, ps aux
 et de recuperer ce qu elle affiche pour l envoyer a l ecran.
 Pour faire ca on utilise :
 - pipe  : un tuyau pour recuperer le resultat de la commande
 - fork  : pour creer une copie du programme qui va lancer la commande
 - execvp: pour lancer la commande dans la copie
 - read  : pour lire ce qui sort du tuyau
 Auteur : Selihe
*/

char	*execute_cmd(char **cmd, int *exit_status)
{
	int		tuyau[2];
	int		pid;
	char	morceau[4096];
	char	*resultat;
	int		total;
	int		lu;
	int		statut;

	/* on cree le tuyau pour recuperer le resultat */
	pipe(tuyau);
	/* on cree une copie du programme */
	pid = fork();
 
	if (pid == 0)
	{
		/* le fils n a pas besoin de lire le tuyau */
		close(tuyau[0]);

		/* on dit au fils d envoyer son resultat dans le tuyau */
		dup2(tuyau[1], 1);

		/* on ferme car on en a plus besoin */
		close(tuyau[1]);

		/* le fils lance la commande ex: date */
		execvp(cmd[0], cmd);

		/* si la commande n existe pas on quitte */
		exit(127);
	}

	/* ici on est dans le programme principal */
	/* le pere n a pas besoin d ecrire dans le tuyau */
	close(tuyau[1]);

	/* ici on gqrde une cqse ;e;oire pour notre progrqmme */
	resultat = malloc(1);
	resultat[0] = '\0';
	total = 0;

	/* on lit le tuyau jusqu a ce qu il soit vide */
	while ((lu = read(tuyau[0], morceau, 4095)) > 0)
	{
		morceau[lu] = '\0';
		resultat = realloc(resultat, total + lu + 1);
		memcpy(resultat + total, morceau, lu + 1);
		total = total + lu;
	}

	/* on ferme le tuyau */
	close(tuyau[0]);
	waitpid(pid, &statut, 0);

	/* on recupere si la commande a reussi ou pas */
	*exit_status = WEXITSTATUS(statut);
	return (resultat);
}
