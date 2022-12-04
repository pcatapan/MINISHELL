/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:11:25 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_execve_and(t_token *token)
{
	if (token->res == 0)
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	exit(1);
}

static void	ft_execve_or(t_token *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				exit(1);
		}
		exit(1);
	}
	if (execve(token->command, token->value, token->main->copy_env))
	{
		printf(RED"%s: coomand not found\n"COLOR_RES, token->value[0]);
		g_exit = 127;
		exit(127);
	}
}

static void	ft_exceve(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_execve_or(token);
		else if (token->prev->and)
			ft_execve_and(token);
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	else
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	exit(1);
}

t_token	*ft_execute_exeve(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	ft_start_execute_(main);
	pidchild = fork();
	if (pidchild != 0)
		ft_parent_execute_(token, pidchild, fd_pipe);
	else
	{
		close(fd_pipe[0]);
		if (token->pipe)
		{
			dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[1]);
		}
		ft_store_matrix(main);
		ft_exceve(token);
	}
	token = ft_end_execute_(token, fd_pipe, main);
	return (token);
}
