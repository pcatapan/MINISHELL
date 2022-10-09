/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/09 22:56:28 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute_command(char *line, t_main *main)
{
	pid_t	pid;
	int		c;
	int		fd[2];
	int		lstsize;
	char	*buffer;

	c = 1;
	pipe(fd);
	buffer = (char *)malloc(sizeof(char) * 8);
	lstsize = ft_lstsize(main->token);
	// ft_print_lst(main->token);
	main->token = ft_return_head(main->token);
	pid = fork();
	while (pid != 0 && c < lstsize)
	{
		close(fd[1]);
		wait(0);
		main->token->next->res = read(fd[0], buffer, 1);
		// printf("%d --- RES\n", main->token->next->res);
		if (main->token->next->res == -1)
			exit(0);
		pid = fork();
		if (pid == -1)
			exit(0);
		main->token = main->token->next;
		c++;
	}
	wait(0);
	if (pid == 0)
	{
		close(fd[0]);
		// printf("%d --- RES IN CHILD\n", main->token->res);
		if (main->token->res == 0 && main->token->or)
			exit(0);
		if (main->token->prev)
		{
			// printf("--%s\n", main->token->value[1]);
			//ft_print_lst(main->token);
			if (main->token->prev->priority == main->token->priority && main->token->res != 0 && !main->token->or)
			{
				//fd[1] = open(fd[1], O_WRONLY);
				write(fd[1], "1", 1);
				// printf("--%s\n", main->token->value[1]);
				exit(0);
			}
		}
		if (execve(main->token->command, main->token->value, main->copy_env))
		{
			perror(RED"ERRORE");
			printf("%s", COLOR_RES);
			write(fd[1], "1", 1);
			exit(0);
			// printf("SCRITTO\n");
		}
	}

	// {
	// 	// check_built_in(main->token->value[0]);
	// 	if (!main->token->command)
	// 		printf("ERRORE CON PATH IN PARSING --LINE 159\n");
	//	// Inserire controllo per i path errati "If command == NULL"
	//	// Cambiare l'outpt della execve
	//	// Implementare Pipex 
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
