/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/10 20:56:45 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_lst(t_token *a)
{
	int	i;

	while (a->prev != NULL)
		a = a->prev;
	while (a)
	{
		i = 0;
		printf("%s --- Command\n", a->command);
		while (a->value[i])
		{
			printf("%s --- Values %d\n", a->value[i], i);
			i++;
		}
		a = a->next;
	}	
}

void	ft_test(t_main *main)
{
	ft_print_lst(main->token);
}

char	*find_path(char *cmd, t_main *main)
{
	char	**paths;
	char	*right_path;
	int		i;
	char	*part_path;

	i = 0;
	// Non trova path nel copy_env
	while (ft_strncmp("PATH=", main->copy_env[i], 5))
	{
		printf("%s\n", main->copy_env[i]);
		i++;
	}
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

void	ft_set_values(char **line, t_main *main)
{
	int	i;
	int	j;

	j = 0;
	while (main->token)
	{
		i = 0;
		main->token->value = (char **)malloc(sizeof(char *) * 3);
		main->token->value[i++] = ft_strdup(main->token->command);
		free(main->token->command);
		main->token->command = find_path(main->token->value[0], main);
		main->token->value[i++] = ft_strdup(line[j]);
		main->token->value[i] = NULL;
		if (!main->token->next)
			break ;
		main->token = main->token->next;
		j++;
	}
}

char	*ft_find_token(char *line, t_main *main)
{
	int		start;
	char	*command;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	command = ft_substr(line, start, end);
	if (!main->token)
		main->token = ft_lstnew(command);
	else
		ft_lstadd_back(&main->token, ft_lstnew(command));
	free(command);
	return (&line[++end]);
}

void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	char	**tmp_value;
	char	*copy_line;
	int		i;
	int		count;

	i = 0;
	count = 1;
	copy_line = ft_strdup(line);
	while (line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i = ft_check_double_quote(line, main, i);
		if (line[i] != 38 && line[i] != 59 && line[i] != 124)
			i++;
		else
		{
			line[i] = 127;
			if (line[i + 1] == 38 || line[i + 1] == 124)
				count++;
			i++;
		}
	}
	tmp = ft_split_original(line, 127);
	tmp_value = (char **)malloc(sizeof(char *) * (count + 1));
	i = -1;
	main->token = NULL;
	// Questo while salva tutta i comandi.
	while (tmp[++i])
		tmp_value[i] = ft_find_token(tmp[i], main);
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_free_matrix(tmp);
	//ft_free_matrix(tmp_value);
	ft_test(main);
}

void	ft_check_command(char *line, t_main *main)
{
	pid_t	pid;

	ft_parsing(line, main);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		//check_built_in(main->token->value[0]);
		if (!main->token->command)
			printf("ERRORE CON PATH IN PARSING --LINE 159\n");
		if (execve(main->token->command, main->token->value, main->copy_env))
			perror(main->token->value[0]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
