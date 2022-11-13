/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 04:12:14 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_new_valus(t_token *token, char *line)
{
	char	**matrix;
	int		i;

	i = 0;
	ft_free_matrix(token->value);
	matrix = ft_split_original(line, 32);
	token->value = (char **)malloc(sizeof(char *) * (ft_matrixlen(matrix) + 1));
	while (matrix[i])
	{
		token->value[i] = ft_strdup(matrix[i]);
		i++;
	}
	token->value[i] = NULL;
}

void	ft_set_new_command(char *str, t_token *token, t_main *main)
{
	char	*command;
	int		i;

	i = 0;
	while (str[i] != 32)
		i++;
	command = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != 32)
	{
		command[i] = str[i];
		i++;
	}
	command[i] = '\0';
	free(token->command);
	token->command = ft_find_path(command, main);
}

void	ft_strjoin_redir(char *f_part, char *line, int fd, t_token *token)
{
	int		start;
	int		end;
	int		i;
	char	*rtr;
	char	*tmp;

	end = ft_strlen(line);
	start = 0;
	while (line[end - start] != '>')
		start++;
	tmp = ft_substr(line, (end - start), start);
	rtr = ft_strjoin(f_part, tmp);
	free(tmp);
	ft_set_new_command(rtr, token, token->main);
	ft_set_new_valus(token, rtr);
	free(token->name_file);
	ft_search_redir(token, ">");
	ft_single_redir(token, token->main);
}

void	ft_execute_multi_redir(t_token *token, t_main *main)
{
	char	*line;
	char	**matrix;
	char	*tmp;
	int		i;
	int		input;

	i = 0;
	line = ft_create_line(token);
	matrix = ft_split_original(line, '>');
	while (matrix[++i])
		input = open(ft_find_name_file(matrix[i]), O_CREAT \
			| O_RDWR, 0644);
	matrix = ft_clear_matrix(matrix);
	tmp = (char *)malloc(sizeof(char) * 1);
	tmp[0] = '\0';
	i = 0;
	while (matrix[i])
		tmp = ft_strjoin(tmp, matrix[i++]);
	ft_free_matrix(matrix);
	ft_strjoin_redir(tmp, line, input, token);
}
