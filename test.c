/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/09/30 17:41:49 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(char **envp){
	int		pid;
	int		pid2;
	char	command[11];
	char	value[2][100];
	int		i;

	pid = fork();
	i = 1;
	command = "/bin/echo";
	value[0] = ft_strdup("Testo1");
	value[1] = ft_strdup("Testo2");
	value[2] = NULL;
	if (pid == -1)
		exit(0);
	while (pid != 0 && i <= 2)
	{
		pid = fork();
		//printf("%d --- i\n", i);
		i++;
	}
	if (pid == 0)
	{
		if (execve(command, value, envp))
			perror("ERRORE\n");
			
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = (t_main *)malloc(sizeof(t_main));
	main->token = (t_token *)malloc(sizeof(t_token));
	if (!main || !main->token)
		return (0);
	main->copy_env = ft_init_envp(envp);
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_prompt(main->copy_env, main);
	ft_free_matrix(main->copy_env);
	free(main);
}