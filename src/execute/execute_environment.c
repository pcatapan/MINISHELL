/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:11:00 by fgrossi           #+#    #+#             */
/*   Updated: 2022/12/03 22:11:28 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parent_exeve(t_token *token, int *fd_pipe, pid_t pidchild)
{
	close(fd_pipe[1]);
	waitpid(pidchild, &token->res, 0);
	if (WIFEXITED(token->res))
		g_exit = WEXITSTATUS(token->res);
}

void	ft_child_exeve(t_token *token, t_main *main, int *fd_pipe)
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

t_token	*ft_execute_exeve(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];
	char	*tmp;

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	tmp = ft_strjoin(main->files_pwd, ".help");
	main->fd_matrix = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
	tmp = ft_strjoin(main->files_pwd, ".export");
	main->fd_export = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
	pidchild = fork();
	if (pidchild != 0)
		ft_parent_exeve(token, fd_pipe, pidchild);
	else
		ft_child_exeve(token, main, fd_pipe);
	token = ft_end_execute_(token, fd_pipe, main);
	return (token);
}

void	ft_execute_even_further(t_main *main)
{
	if (!main->token->heredoc)
		ft_execute_dollar(main->token, main);
	if (ft_strchr(main->token->value[0], '=') \
			&& ft_check_envi(main->token->value[0]))
			main->token = \
			ft_execute_enviroment(main->token, main->token->value[0]);
	else if (main->token->input || main->token->append || \
		main->token->output || main->token->heredoc || main->redirections)
			main->token = ft_redirections(main->token, main);
	else if (ft_check_builtin(main->token) && !main->redirections)
			main->token = ft_execute_builtin(main->token, main);
	else
			main->token = ft_execute_exeve(main->token, main);
	ft_check_dir(main);
}

void	ft_execute_command(t_main *main)
{
	int		lstsize;

	main->count = 0;
	lstsize = ft_lstsize(main->token);
	main->token = ft_return_head(main->token);
	while (main->count < lstsize)
	{
		ft_execute_even_further(main);
		main->count++;
	}
}
