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

void	ft_search_builtin(t_token *token)
{
	//Sostituire la chiamata diretta alla funzone con una chiamta di controllo,
	// per verifivare condiione and e or, controllare ft_exceve, per delucidazioni
	if (ft_strcmp(token->value[0], "echo"))
		ft_check_echo(token);
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
	exit(0);
}

t_token	*ft_execute_builtin(t_token *token)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
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
		ft_search_builtin(token);
	}
	token = ft_end_execute_(token, fd_pipe);
	return (token);
}
