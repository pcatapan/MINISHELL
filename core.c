/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:16:37 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/29 20:52:36 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include <termcap.h>
#include <sys/types.h>
#include <stdlib.h>
#include <curses.h>

int main(int argv, char **args, char **envp)
{
	pid_t	pid, wpid;
	int	status;
	char 	*cmd;

	cmd = "/bin/ls";
	pid = fork();
	if (pid == 0) {
		// Child process
		if (execve(cmd, args, envp) == -1) {
			perror(cmd);
			}
		exit(EXIT_FAILURE);
/*
Se il comando exec restituisce -1 (o effettivamente, se restituisce del tutto),
sappiamo che si è verificato un errore. Quindi, utilizziamo perrorper stampare il messaggio di errore del sistema,
insieme al nome del nostro programma, in modo che gli utenti sappiano da dove proviene l'errore.
Quindi, usciamo in modo che la shell possa continuare a funzionare.
*/
	}
	else if (pid < 0) {
		// Error forking
		perror("lsh");
	} else {
		// Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
/*
La terza condizione significa che fork()è stata eseguita con successo.
Il processo genitore atterrerà qui. Sappiamo che il bambino eseguirà il processo, quindi
il genitore deve attendere che il comando termini l'esecuzione.
*/
	return 1;
}