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

t_token	*ft_return_head(t_token *list)
{
	while (list)
	{
		list = list->prev;
		if (!list->prev)
			break ;
	}
	return (list);
}

void	ft_print_lst(t_token *a)
{
	int	i;

	while (a->prev != NULL)
		a = a->prev;
	while (a)
	{
		printf("%d\n", a->and);
		printf("%d\n", a->or);
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
	while (ft_strncmp("PATH=", main->copy_env[i], 5))
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

int	ft_count_array(char *line, t_main *main)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
			count++;
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] != 32 && line[i - 1] == 32)
			count++;
		i++;
	}
	return (count);
}

void	ft_divide_line(char *line, t_main *main)
{
	int		count;
	int		i;
	char	**tmp;

	i = -1;
	count = ft_count_array(line, main);
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == 32)
			line[i] = 127;
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34 || line[i] == 39)
			line[i] = 127;
	}
	tmp = ft_split_original(line, 127);
	i = 0;
	while (tmp[i])
	{
		main->token->value[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	main->token->value[i + 1] = NULL;
}

void	ft_set_values(char **line, t_main *main)
{
	int	j;

	j = 0;
	while (main->token)
	{
		main->token->value = (char **)malloc(sizeof(char *) * \
							(ft_count_array(line[j], main) + 2));
		main->token->value[0] = ft_strdup(main->token->command);
		free(main->token->command);
		main->token->command = find_path(main->token->value[0], main);
		ft_divide_line(line[j], main);
		if (!main->token->next)
			break ;
		main->token = main->token->next;
		j++;
	}
	main->token = ft_return_head(main->token);
	// while (main->token)
	// {
	// 	j = -1;
	// 	while (main->token->value[++j])
	// 		printf("%s\n", main->token->value[j]);
	// 	if (!main->token->next)
	// 		break ;
	// 	main->token = main->token->next;
	// }
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

void	ft_set_op_logic(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		while (line[i])
		{
			if(line[i] == '&' || line[i] =='|')
				break ;
			i++;
		}
		i++;
		if (line[i] == '&')
			token->and = true;
		else if (line[i] == '|')
			token->or = true;
		i++;
		if(!token->next)
			break;
		token = token->next;
	}
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
	// Questo while salva tutti i comandi.
	while (tmp[++i])
		tmp_value[i] = ft_find_token(tmp[i], main);
	tmp_value[i] = NULL;
	// i = -1;
	// while (tmp_value[++i])
	// 	printf("%s --- TMP VALUE\n", tmp_value[i]);
	// ft_free_matrix(tmp);
	ft_set_values(tmp_value, main);
	ft_set_op_logic(copy_line, main->token);
	//ft_free_matrix(tmp_value);
	// ft_test(main);
}

void	ft_check_command(char *line, t_main *main)
{
	pid_t	pid;

	ft_parsing(line, main);
	main->token = ft_return_head(main->token);
	while (main->token)
	{
		ft_print_lst(main->token);
		if (!main->token->next)
			break ;
		main->token = main->token->next;
	}
	// pid = fork();
	// if (pid == -1)
	// 	exit(0);
	// if (pid == 0)
	// {
	// 	//check_built_in(main->token->value[0]);
	// 	if (!main->token->command)
	// 		printf("ERRORE CON PATH IN PARSING --LINE 159\n");
	// 	if (execve(main->token->command, main->token->value, main->copy_env))
	// 		perror(main->token->value[0]);
	// 	exit(0);
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
