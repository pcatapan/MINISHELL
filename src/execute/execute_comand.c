/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/20 04:56:12 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_qualcosa(t_token *token, t_main *main)
{
	ft_execute_dollar(token);
	// if (ft_check_builtin(token))
	// 	token = ft_execute_builtin(token);
	/*else */if (ft_strchr(token->value[0], '=') && ft_check_envi(token->value[0]))
		token = ft_execute_enviroment(token, token->value[0]);
	else // Qui entra se il comando bultin é errato o se non é da gestirte
		token = ft_execute_exeve(token, main);
	exit(token->res);
}

void	ft_exceve(t_token *token)
{
	// if (token->priority != 0)
	// 	ft_execve_priority(token);
	if (token->prev)
	{
		if (token->prev->or)
			ft_execve_or(token);
		else if (token->prev->and)
			ft_execve_and(token);
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			exit(1);
		}
	}
	else
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			exit(1);
		}
	}
	exit(1);
}

t_token	*ft_execute_exeve(t_token *token, t_main *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	pipe(fd_pipe);
	main->fd_matrix = open(ft_strjoin(main->files_pwd, "irina"),
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	main->fd_export = open(ft_strjoin(main->files_pwd, "export"),
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd_pipe[1]);
		waitpid(pidchild, &token->res, 0);
	}
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

void	ft_check_dir(t_main *main)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0
			&& pwd != ft_substr(main->copy_env[i],
				4, ft_strlen(main->copy_env[i])))
		{
			pwd = ft_substr(main->copy_env[i], 4, ft_strlen(main->copy_env[i]));
			chdir(pwd);
		}
		i++;
	}
}

void	ft_execute_command(char *line, t_main *main)
{
	pid_t	pidchild;
	int		lstsize;

	main->count = 0;
	lstsize = ft_lstsize(main->token);
	main->token = ft_return_head(main->token);
	while (main->count < lstsize)
	{
		ft_execute_dollar(main->token);
		if (main->token->priority != 0)
			main->token = ft_priority(main->token, main->token->priority, main);
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
		main->count++;
	}
}
