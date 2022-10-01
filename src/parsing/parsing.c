/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/09/30 15:38:56 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_lst(t_token *token)
{
	int	i;
	t_token *a;

	a = ft_return_head(token);
	while (a)
	{
		printf("%s --- Comand\n", a->command);
		i = -1;
		while (a->value[++i] != NULL)
			printf("%s --- Value %d\n", a->value[i], i);
		printf("%d -- Priority\n", a->priority);
		printf("%d -- Bool Res\n", a->res);
		printf("%d -- Bool And\n", a->and);
		printf("%d -- Bool Or\n", a->or);
		if (!a->next)
			break ;
		a = a->next;
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
	while (tmp[++i])
		tmp_value[i] = ft_find_token(tmp[i], main);
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_set_priority(copy_line, main, 0);
	ft_set_op_logic(copy_line, main->token);
}

char	*ft_change_var_in_dollar(int start, int l, char* str, char** copy_env)
{
	char	*first_part;
	char	*second_part;
	char	*word;
	char	*insert_word;

	first_part = ft_substr(str, 0, start - 1);
	second_part = ft_substr(str, start + l, ft_strlen(str));
	word = ft_substr(str, start, l);
	insert_word = ft_searchstrchr(ft_strjoin(word, "="), copy_env);
	free(word);
	word = ft_strjoin(first_part, insert_word);
	free(insert_word);
	free(first_part);
	free(str);
	str = ft_strjoin(word, second_part);
	free(second_part);
	return (str);
}

char	*ft_expand_dollar(char *line, char **copy_env)
{
	int	i;
	int	l;
	int	start;

	i = 0;
	l = 0;
	start = 0;
	while (line[i] != '$' && line[i])
		i++;
	if (line[i] == '$')
		start = i + 1;
	while (line[++i] != ' ' && line[i])
		l++;
	if (start != 0)
		line = ft_change_var_in_dollar(start, l, line, copy_env);
	return (line);
}

void	ft_check_command(char *line, t_main *main)
{
	pid_t	pid;
	int		c;
	int		tmp;

	c = 1;
	tmp = ft_lstsize(main->token);
	if (main->dub_quotes != 0)
		line = ft_expand_dollar(line, main->copy_env);
	ft_parsing(line, main);
	//ft_print_lst(main->token);
	main->token = ft_return_head(main->token);
	// if (!main->token)
	// 	printf("NON ESISTE\n");
	pid = fork();
	while (pid != 0 && c < 2)
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		c++;
	}
	if (pid == 0)
	{
		printf("%d\n", c);
		if (execve(main->token->command, main->token->value, main->copy_env))
			perror("ERRORE\n");
		if (main->token->next)
			main->token = main->token->next;
		exit(0);
	}
	// {
	// 	// check_built_in(main->token->value[0]);
	// 	if (!main->token->command)
	// 		printf("ERRORE CON PATH IN PARSING --LINE 159\n");
	//	// Inserire controllo per i path errati "If command == NULL"
	//	// Cambiare l'outpt della execve
	//	// Implementare Pipex 
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
