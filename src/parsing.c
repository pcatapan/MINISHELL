/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/13 18:10:28 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_return_head(t_token *list)
{
	while (list)
	{
		if (!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

void	ft_print_lst(t_token *a)
{
	int	i;

	printf("%s --- Comand\n", a->command);
	i = -1;
	while (a->value[++i])
		printf("%s --- Value %d\n", a->value[i], i);
	printf("%d -- Priority\n", a->priority);
	printf("%d -- Bool Res\n", a->res);
	printf("%d -- Bool And\n", a->and);
	printf("%d -- Bool Or\n", a->or);
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

char	*ft_clear_value(char *str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = 0;
	i = 0;
	if (str[0] == 34 || str[0] == 39)
		start = 1;
	while (str[i + start])
		i++;
	if (str[i] == 34 || str[i] == 39)
		end = i - 1;
	return (ft_substr(str, start, end));
}

void	ft_divide_line(char *line, t_main *main)
{
	int		i;
	char	**tmp;
	char	*tmp_comand;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == 32 || line[i] == 41)
			line[i] = 127;
	}
	// i = -1;
	// while (line[++i])
	// {
	// 	if (line[i] == 34 || line[i] == 39)
	// 		line[i] = 127;
	// }
	tmp = ft_split_original(line, 127);
	i = 0;
	while (tmp[i])
	{
		tmp_comand = ft_strdup(tmp[i]);
		main->token->value[i + 1] = ft_clear_value(tmp_comand);
		free(tmp_comand);
		i++;
	}
	main->token->value[i + 1] = NULL;
}

/*
Aggiungere funzione per settare priorita, ideale prima dello strudup
prima di passare a path bisogna pulire il paramentro da eventuali '('
come chiuderla?
*/
void	ft_set_values(char **line, t_main *main)
{
	int	j;

	j = 0;
	while (main->token)
	{
		main->token->value = (char **)malloc(sizeof(char *) * \
							(ft_count_array(line[j], main) + 2));
		main->token->value[0] = ft_strdup(main->token->command);
		printf("%s -- Value in ft_set_values\n", main->token->value[0]);
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

/*
Altra ipotesi per gestire le () farle saltre sullo start e end
successivamnte andare a fare check sulla copy, come fatto con gli op_logic
!Soluzione che al momento mi sembra la migliore
*/
char	*ft_find_token(char *line, t_main *main)
{
	int		start;
	char	*command;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ' || line[start] == '(')
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
			if (line[i] == '&' || line[i] == '|')
				break ;
			i++;
		}
		i++;
		if (line[i] == '&')
			token->and = true;
		else if (line[i] == '|')
			token->or = true;
		i++;
		if (!token->next)
			break ;
		token = token->next;
	}
}

void	ft_set_priority(char *line, t_token *token, int brack)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	while (token)
	{
		while (line[i])
		{
			if (line[i] == '(' && first)
				token->priority = brack;
			else if (line[i] == '(' && !first)
				ft_set_priority(&line[i], token, brack + 1);
			else if (line[i] == ')' && line[i + 1])
				ft_set_priority(&line[i], token, brack - 1);
			if (line[i++] == '&' || line[i] == '|')
				break ;
			i++;
		}
		printf("%s -- Comand\n", token->value[0]);
		//i += 2;
		token->priority = brack;
		i++;
		if (!token->next)
			break ;
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
	ft_set_priority(copy_line, main->token, 1);
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
