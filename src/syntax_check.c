/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:59:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/06 16:37:12 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_double_quote(char *line, t_main *main)
{
	int	i;

	i = 0;
	main->quotes = 0;
	while (line[i] && line)
	{
		if (line[i] == '"' && line[i - 1] != 92)
			main->quotes++;
		i++;
	}
	return (i);
}

int	ft_check_single_quote(char *line, t_main *main)
{
	int	i;

	i = 0;
	main->quotes = 0;
	while (line[i] && line)
	{
		if (line[i] == 39)
			main->quotes++;
		i++;
	}
	return (i);
}

void	ft_check_syntax(char *line, t_main *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i = ft_check_double_quote(line, main);
			if (main->quotes % 2 != 0)
				ft_putendl_fd(RED ERROR_DOUBLE_QUOTE COLOR_RES, STDOUT_FILENO);
		}
		else if (line[i] == 39)
		{
			i = ft_check_single_quote(line, main);
			if (main->quotes % 2 != 0)
				ft_putendl_fd(RED ERROR_SING_QUOTE COLOR_RES, STDOUT_FILENO);
		}
		if (!line[i])
			break ;
		if (line[i] == 92)
			ft_putendl_fd(RED ERROR_BACKSLASH COLOR_RES, STDOUT_FILENO);
		i++;
	}
	if (ft_strchr(line, '=') == 1 && ft_check_envi(line) == 1)
		main->copy_env = ft_add_envi(line, main);
}


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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
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
		main->token->value = (char **)malloc(sizeof(char *) * 2);
		if (!main->token->value)
			return ;
		while (line[start] == ' ')
			start++;
		while (line[start + end] != ' ' && line[start + end] != '\0')
			end++;
		main->token->value[0] = ft_substr(line, start, end);
		check_built_in(main->token->value[0]);
		path = find_path(main->token->value[0], main);
		if (!path)
			perror("Error");
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

// void	ft_check_command(char *line, t_main *main)
// {
// 	int		start;
// 	int		end;
// 	pid_t	pid;

// 	start = 0;
// 	end = 0;
// 	main->token->value = (char **)malloc(sizeof(char *) * 2);
// 	if (!main->token->value)
// 		return ;
// 	while (line[start] == ' ')
// 		start++;
// 	while (line[start + end] != ' ' && line[start + end] != '\0')
// 		end++;
// 	main->token->value[0] = ft_substr(line, start, end);
// 	main->token->token = ft_strjoin("/bin/", main->token->value[0]);
// 	main->token->value[1] = NULL;
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (pid == 0)
// 	{
// 		// Child process
// 		if (execve(main->token->token, main->token->value, main->copy_env))
// 			perror(main->token->value[1]);
// 		exit(0);
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// }

	


