/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 03:04:11 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_search_builtin(t_token *token, t_main *main)
{
	if (ft_strcmp(token->value[0], "echo"))
		ft_check_echo(token);
	else if (ft_strcmp(token->value[0], "env"))
		ft_env(main);
	else if (ft_strcmp(token->value[0], "unset"))
		ft_unset(token, main);
	else if (ft_strcmp(token->value[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(token->value[0], "cd"))
		ft_cd(token, main);
	else if (ft_strcmp(token->value[0], "export"))
		ft_export(token, main);
	else if (ft_strcmp(token->value[0], "exit"))
		ft_exit(token);
}

t_token	*ft_execute_builtin(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	main->fd_matrix = open(ft_strjoin(main->files_pwd, "irina"),
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	main->fd_export = open(ft_strjoin(main->files_pwd, "export"),
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd_pipe[1]);
		waitpid(pidchild, &token->res, 0);
		if (token->res == 768)
			exit(0);
	}
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
