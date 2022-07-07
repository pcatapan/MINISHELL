/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/07 16:35:25 by pcatapan         ###   ########.fr       */
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

char	*ft_find_token(char *line, t_main *main)
{
	int		start;
	char	*command;
	t_token	*tmp;
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
	{
		tmp = ft_lstnew(command);
		ft_lstadd_back(&main->token, tmp);
		printf("Maledetto\n");
	}
	free(command);
	return (&line[++end]);
}

void	ft_set_values(char *line, t_main *main)
{
	char	*charset;
	char	**tmp;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i = ft_check_double_quote(line, main, i);
		if (line[i] != 38 && line[i] != 59 && line[i] != 124)
			i++;
		else
		{
			count++;
			i++;
		}
	}
	tmp = (char **)malloc(sizeof(char *) * count);
	if (!tmp)
		return ;
	
}

//	"'; & | "
void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	int		i;
	char	*copy_line;

	i = 0;
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
			i++;
		}
	}
	tmp = ft_split_original(line, 127);
	i = -1;
	while (tmp[++i])
		ft_find_token(tmp[i], main);
	i = -1;
	while (main->token->value[++i])
		printf("%s\n", main->token->value[i]);
	//ft_set_values(tmp, main);
}

void	ft_check_command(char *line, t_main *main)
{
	//char	*path;
	//pid_t	pid;

	ft_parsing(line, main);
	// pid = fork();
	// if (pid == -1)
	// 	exit(0);
	// if (pid == 0)
	// {
	// 	main->token->value = (char **)malloc(sizeof(char *) * 4);
	// 	if (!main->token->value)
	// 		return ;
	// 	// main->token->value dovrebbe essere riempito dallo split - Parsering
	// 	main->token->value[1] = ft_strdup("testo ' messaggio");
	// 	main->token->value[2] = ft_strdup("PROVA");
	// 	main->token->value[3] = NULL;
	// 	//check_built_in(main->token->value[0]);
	// 	path = find_path(main->token->value[0], main);
	// 	if (!path)
	// 		printf("ERRORE CON PATH IN PARSING --LINE 69\n");
	// 	if (execve(path, main->token->value, main->copy_env))
	// 		perror(main->token->value[1]);
	// 	exit(0);
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
