/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/26 02:58:40 by pcatapan         ###   ########.fr       */
=======
/*   Updated: 2022/11/20 19:57:13 by aanghel          ###   ########.fr       */
>>>>>>> parent of d679adb... fix primi leaks echo ciao
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
}

t_token	*ft_execute_builtin(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];
	char	*irina;
	char	*export;

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	irina = ft_strjoin(main->files_pwd, "irina");
	main->fd_matrix = open(irina, O_CREAT | O_RDWR | O_TRUNC, 0644);
	export = ft_strjoin(main->files_pwd, "export");
	main->fd_export = open(export, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(irina);
	free(export);
	if (ft_strcmp(token->value[0], "exit"))
		ft_exit(token);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd_pipe[1]);
		waitpid(pidchild, &token->res, 0);
		if (WIFEXITED(token->res))
			g_exit = WEXITSTATUS(token->res);
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
