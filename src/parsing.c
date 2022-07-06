/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/06 17:40:02 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_path(char *cmd, t_main *main)
{
	char	**paths;
	char	*right_path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(main->copy_env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(main->copy_env[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		right_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(right_path, F_OK) == 0)
			return (right_path);
		free(right_path);
		i++;
	}
	ft_free_matrix(paths);
	return (0);
}

void	ft_check_command(char *line, t_main *main)
{
	char	*path;
	int		start;
	int		end;
	pid_t	pid;

	start = 0;
	end = 0;
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		main->token->value = (char **)malloc(sizeof(char *) * 4);
		if (!main->token->value)
			return ;
		while (line[start] == ' ')
			start++;
		while (line[start + end] != ' ' && line[start + end] != '\0')
			end++;
		// main->token->value dovrebbe essere riempito dallo split - Parsering
		main->token->value[0] = ft_substr(line, start, end);
		main->token->value[1] = ft_strdup("testo ' messaggio");
		main->token->value[2] = ft_strdup("PROVA");
		main->token->value[3] = NULL;
		//check_built_in(main->token->value[0]);
		path = find_path(main->token->value[0], main);
		if (!path)
			printf("ERRORE CON PATH IN PARSING --LINE 69\n");
		if (execve(path, main->token->value, main->copy_env))
			perror(main->token->value[1]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void check_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 1)
		ft_exit();
	if (ft_strcmp(cmd, "env") == 1)
		ft_env();
	if (ft_strcmp(cmd, "unset") == 1)
		ft_unset();
	if (ft_strcmp(cmd, "pwd") == 1)
		ft_pwd();
	if (ft_strcmp(cmd, "cd") == 1)
		ft_cd();
	if (ft_strcmp(cmd, "echo") == 1)
		ft_echo();
	if (ft_strcmp(cmd, "export") == 1)
		ft_export();
}

void ft_exit(void)
{
	exit(1);
}

void ft_env(void)
{
	exit(1);
}

void ft_unset(void)
{
	exit(1);
}

void ft_pwd(void)
{
	exit(1);
}

void ft_cd(void)
{
	exit(1);
}

void ft_echo(void)
{
	exit(1);
}

void ft_export(void)
{
	exit(1);
}
