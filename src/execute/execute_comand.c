/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/10 05:37:03 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execve(t_main *main, pid_t pid, int fd[2])
{
	pid_t	pidchild;

	pidchild = fork();
	if (pidchild == 0)
	{
		if (main->token->next)
		{
			main->token = main->token->next;
			main->token->res = 1;
			printf("EXECVE -- RES:%d --- Value: %s\n", main->token->res, main->token->value[1]);
			ft_loop_command(main, fd);
		}
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
	exit(0);
}

void	ft_loop_command(t_main *main, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (main->token->res == 0 && main->token->or)
		{
			// printf("RES:%d --- Value: %s --- OR:%d\n", main->token->res, main->token->value[1], main->token->or);
			if (execve(main->token->command, main->token->value, main->copy_env))
			{
				perror(RED"ERRORE1"COLOR_RES);
				write(fd[1], "1", 1);
				exit(0);
			}
			exit(0);
		}
		if (main->token->prev)
		{
			if (main->token->prev->priority == main->token->priority \
				&& main->token->res != 0 && main->token->prev->and)
			{
				// printf("RES:%d --- Value: %s\n", main->token->res, main->token->value[1]);
				ft_execve(main, pid, fd);
				exit(0);
			}
			if (main->token->prev->priority == main->token->priority \
				&& main->token->res == 0 && main->token->prev->or)
				exit(0);
		}
		if (execve(main->token->command, main->token->value, main->copy_env))
		{
			perror(RED"ERRORE2"COLOR_RES);
			printf("RES:%d --- Value: %s\n", main->token->res, main->token->value[1]);
			ft_execve(main, pid, fd);
			exit(0);
		}
	}
	else
	{
		close(fd[1]);
		waitpid(pid, 0, 0);
	}
}

void	ft_execute_command(char *line, t_main *main)
{
	int		c;
	int		fd[2];
	int		lstsize;
	char	*buffer;

	c = 0;
	pipe(fd);
	buffer = (char *)malloc(sizeof(char) * 8);
	lstsize = ft_lstsize(main->token);
	// ft_print_lst(main->token);
	main->token = ft_return_head(main->token);
	while (c < lstsize)
	{
		ft_print_lst(main->token);
		ft_loop_command(main, fd);
		if (main->token->next)
			main->token = main->token->next;
		c++;
	}
	// wait(0);
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	if (main->token->or)
	// 		exit(0);
	// 	if (main->token->prev)
	// 	{
	// 		if (main->token->prev->priority == main->token->priority \
	// 			&& main->token->res != 0 && !main->token->or)
	// 		{
	// 			write(fd[1], "1", 1);
	// 			exit(0);
	// 		}
	// 	}
	// 	if (execve(main->token->command, main->token->value, main->copy_env))
	// 	{
	// 		perror(RED"ERRORE");
	// 		printf("%s", COLOR_RES);
	// 		write(fd[1], "1", 1);
	// 		exit(0);
	// 	}
	// }
}
