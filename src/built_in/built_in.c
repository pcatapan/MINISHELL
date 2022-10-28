/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 19:04:08 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_execute_builtin(t_token *token)
{
	pid_t	pidchild;
	int		fd_pipe[2];
	int		fd[2];

	if (pipe(fd) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd[1]);
		close(fd_pipe[1]);
		waitpid(pidchild, NULL, 0);
	}
	else
	{
		close(fd[0]);
		close(fd_pipe[0]);
		if (token->pipe)
			dup2(fd_pipe[1], STDOUT_FILENO);
		ft_search_builtin(token, fd);
	}
	token = ft_end_execute_(token, fd_pipe);
	return (token);
}

void	ft_search_builtin(t_token *token, int fd[2])
{
	if (ft_strcmp(token->value[0], "echo"))
		ft_echo(token, fd);
	else if (ft_strcmp(token->value[0], "env"))
		ft_env(token);
	else if (ft_strcmp(token->value[0], "unset"))
		ft_unset(token);
	else if (ft_strcmp(token->value[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(token->value[0], "cd"))
		ft_cd(token);
	else if (ft_strcmp(token->value[0], "export"))
		ft_export(token);
	else if (ft_strcmp(token->value[0], "exit"))
		ft_exit(token);
	// else
	// 	ft_exceve(token, fd);
}
