/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:14:05 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/23 01:20:53 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h> 
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
/*
envp racchiude tutte le variabili di ambinete attualmente dichiarate
Non è una variabile che si può modificare, bisognera copiarla e lavorare sulla copia
Dopo averlo copiato ci saranno dei valori da modificare
	- SHELL \\Nome della shell
	- SHLVL \\Numero di livello del terminale
*/
	int	i;

	i  = 0;
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("\nQuesta è tutto");
}
