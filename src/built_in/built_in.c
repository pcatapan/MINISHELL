/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/16 00:23:22 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_serach_builtin(t_token *token, int fd[2], int fd_pipe[2])
{
	if (ft_strcmp(token->value[0], "echo"))
		ft_echo(token, fd);
	// else if (ft_strcmp(token->value[0], "env"))
	// else if (ft_strcmp(token->value[0], "unset"))
	// else if (ft_strcmp(token->value[0], "pwd"))
	// else if (ft_strcmp(token->value[0], "cd"))
	// else if (ft_strcmp(token->value[0], "export"))
	// else if (ft_strcmp(token->value[0], "exit"))
}

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
		close(fd[1]);//Close Write
		close(fd_pipe[1]);
		waitpid(pidchild, NULL, 0);
	}
	else
	{
		close(fd[0]);//Close Read
		close(fd_pipe[0]);
		if (token->pipe)
			dup2(fd_pipe[1], STDOUT_FILENO);
		ft_serach_builtin(token, fd, fd_pipe);
	}
	ft_end_execute_(token, fd, fd_pipe);
	return (token);
}
