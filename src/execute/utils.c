/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:43:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:22:39 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parent_execute_(t_token *token, pid_t pidchild, int fd_pipe[2])
{
	close(fd_pipe[1]);
	waitpid(pidchild, &token->res, 0);
	if (WIFEXITED(token->res))
		g_exit = WEXITSTATUS(token->res);
}

void	ft_start_execute_(t_main *main)
{
	char	*tmp;

	tmp = ft_strjoin(main->files_pwd, ".help");
	main->fd_matrix = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
	tmp = ft_strjoin(main->files_pwd, ".export");
	main->fd_export = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
}

t_token	*ft_end_execute_(t_token *token, int fd_pipe[2], t_main *main)
{
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
		token->dup = token->prev->dup;
	}
	if (token->prev && token->prev->pipe && token->stdinput == STDIN_FILENO)
	{
		token->dup = dup(STDIN_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		token->stdinput = fd_pipe[0];
		close(fd_pipe[0]);
	}
	else if (token->stdinput != token->dup)
		dup2(token->dup, STDIN_FILENO);
	ft_free_matrix(main->copy_env);
	ft_free_matrix(main->export_env);
	main->copy_env = ft_get_next_line(main->fd_matrix, \
			ft_strjoin(main->files_pwd, ".help"));
	main->export_env = ft_get_next_line(main->fd_export, \
			ft_strjoin(main->files_pwd, ".export"));
	return (token);
}

void	ft_store_matrix(t_main *main)
{
	int		i;

	i = 0;
	while (main->copy_env[i])
	{
		write(main->fd_matrix, main->copy_env[i], ft_strlen(main->copy_env[i]));
		write(main->fd_matrix, "\n", 1);
		i++;
	}
	close(main->fd_matrix);
	i = 0;
	while (main->export_env[i])
	{
		write(main->fd_export, main->export_env[i],
			ft_strlen(main->export_env[i]));
		write(main->fd_export, "\n", 1);
		i++;
	}
	close(main->fd_export);
}

void	ft_check_dir(t_main *main)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0)
		{
			free(pwd);
			pwd = ft_substr(main->copy_env[i], 4, ft_strlen(main->copy_env[i]));
			chdir(pwd);
		}
		i++;
	}
	free(pwd);
}
