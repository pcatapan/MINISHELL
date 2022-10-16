/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/16 17:51:10 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_cd(t_token *token, int fd[2])
{
	char *tmp;
	int i;
	
	i = 0;
	if (token->value[1] == NULL)
		return;
	if (chdir(token->value[1]) == -1)
		ft_printf(RED"cd: %s: No such file or directory\n"COLOR_RES, token->value[1]);
	else
	{
		chdir(token->value[1]);
		while(token->main->copy_env[i])
		{
			if (ft_strncmp(token->main->copy_env[i], "PWD=", 4) == 0)
			{
				tmp = getcwd(NULL, 0);
				free(token->main->copy_env[i]);
				token->main->copy_env[i] = ft_strjoin("PWD=", tmp);
				free(tmp);
			}
			i++;
		}
	}
}

void ft_pwd(t_token *token, int fd[2])
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
}

void ft_env(t_token *token, int fd[2])
{
	int i;

	i = 0;
	printf("nostro\n");
	while (token->main->copy_env[i])
	{
		ft_printf("%s\n", token->main->copy_env[i]);
		i++;
	}
}

void ft_unset(t_token *token, int fd[2])
{
	int i;
	int j;

	i = 1;
	while (token->value[i])
	{
		j = 0;
		while (token->main->copy_env[j])
		{
			if (ft_strncmp(token->value[i], token->main->copy_env[j], ft_strlen(token->value[i])) == 0)
			{
				free(token->main->copy_env[j]);
				token->main->copy_env[j] = NULL;
				while(token->main->copy_env[j + 1])
				{
					token->main->copy_env[j] = token->main->copy_env[j + 1];
					j++;
				}
			}
			j++;
		}
		i++;
	}
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
		ft_search_builtin(token, fd, fd_pipe);
	}
	ft_end_execute_(token, fd, fd_pipe);
	return (token);
}

void	ft_search_builtin(t_token *token, int fd[2], int fd_pipe[2])
{

	if (ft_strcmp(token->value[0], "echo"))
		ft_echo(token, fd);
	 else if (ft_strcmp(token->value[0], "env"))
	 	ft_env(token, fd);
	else if (ft_strcmp(token->value[0], "unset"))
		ft_unset(token, fd);
	else if (ft_strcmp(token->value[0], "pwd"))
		ft_pwd(token, fd);
	else if (ft_strcmp(token->value[0], "cd"))
		ft_cd(token, fd);
	// else if (ft_strcmp(token->value[0], "export"))
	// 	ft_export(token, fd);
	// else if (ft_strcmp(token->value[0], "exit"))
	// 	ft_exit(token, fd);
	// else
	// 	ft_exceve(token, fd);
	// else if (ft_strcmp(token->value[0], "export"))
	// else if (ft_strcmp(token->value[0], "exit"))
}