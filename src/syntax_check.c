/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:59:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/05 20:11:52 by pcatapan         ###   ########.fr       */
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

void	ft_check_command(char *line, t_main *main)
{
	int		start;
	int		end;
	pid_t	pid;

	start = 0;
	end = 0;
	main->token->value = (char **)malloc(sizeof(char *) * 2);
	if (!main->token->value)
		return ;
	while (line[start] == ' ')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	main->token->value[0] = ft_substr(line, start, end);
	main->token->token = ft_strjoin("/bin/", main->token->value[0]);
	main->token->value[1] = NULL;
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		// Child process
		if (execve(main->token->token, main->token->value, main->copy_env))
			perror(main->token->value[1]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
