/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/12 22:51:19 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_set_to_del(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			line[i] = 127;
		i++;
	}
	return (line);
}

char	*ft_create_line(t_token *token)
{
	char	*tmp;
	char	*val;
	int		i;

	if (!(tmp = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	i = 0;
	tmp = "\0";
	while (token->value[i])
	{
		val = ft_strjoin(token->value[i], " ");
		tmp = ft_strjoin(tmp, val);
		free(val);
		i++;
	}
	return (tmp);
}

char	*ft_find_name_file(char *str)
{
	int		start;
	int		end;
	int		delete;
	char	*rtr;

	start = 0;
	end = 0;
	while (str[start] == 32)
		start++;
	while (str[start + end] != 32)
		end++;
	rtr = ft_substr(str, start, end);
	delete = start + end;
	while (delete != -1)
		str[delete--] = 127;
	return (rtr);
}

void	ft_execute_multi_redir(t_token *token)
{
	char	*line;
	char	**matrix;
	int		i;
	int		input;
	// int		ouput;

	// ft_print_lst(token);
	i = 0;
	line = ft_create_line(token);
	matrix = ft_split_original(line, '>');
	while (matrix[++i])
		input = open(ft_find_name_file(matrix[i]), O_CREAT | O_RDWR, 0644);
	i = 0;
	while (matrix[i])
		printf("%s\n", matrix[i++]);
	// ft_set_info(matrix, main, main->copy_line, 1);
	// ft_print_lst(main->token);
	// while (main->token)
	// {
	// if (main->token->command == NULL || ft_strcmp(main->token->command, "bin/file"))
	// 	main->token = main->token->next;
	// }
}
