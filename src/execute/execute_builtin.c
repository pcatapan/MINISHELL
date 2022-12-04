/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 21:59:00 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_search_builtin(t_token *token, t_main *main)
{
	if (ft_strcmp(token->value[0], "echo") || \
			ft_strcmp(token->value[0], "/bin/echo"))
		ft_check_echo(token);
	else if (ft_strcmp(token->value[0], "env"))
		ft_env(main);
	else if (ft_strcmp(token->value[0], "unset"))
		ft_unset(token, main);
	else if (ft_strcmp(token->value[0], "pwd") || \
			ft_strcmp(token->value[0], "/bin/pwd"))
		ft_pwd();
	else if (ft_strcmp(token->value[0], "cd"))
		ft_cd(token, main);
	else if (ft_strcmp(token->value[0], "export"))
		ft_export(token, main);
}

t_token	*ft_execute_builtin(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	ft_start_execute_(main);
	if (ft_strcmp(token->value[0], "exit"))
		ft_exit(token);
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
		ft_search_builtin(token, main);
		ft_store_matrix(main);
		exit(0);
	}
	token = ft_end_execute_(token, fd_pipe, main);
	return (token);
}
