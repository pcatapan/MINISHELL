/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 20:47:44 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_redirection(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], ">") \
			|| ft_strcmp(token->value[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

void	ft_set_new_valus(t_token *token, char *line)
{
	char	**matrix;
	int		i;

	i = 0;
	ft_free_matrix(token->value);
	matrix = ft_split_original(line, 32);
	token->value = (char **)malloc(sizeof(char *) * (ft_matrixlen(matrix) + 1));
	if (!token->value)
		return ;
	while (matrix[i])
	{
		token->value[i] = ft_strdup(matrix[i]);
		i++;
	}
	token->value[i] = NULL;
	ft_free_matrix(matrix);
}

void	ft_set_new_command(char *str, t_token *token, t_main *main)
{
	char	*command;
	int		i;

	i = 0;
	while (str[i] != 32)
		i++;
	command = (char *)malloc(sizeof(char) * i + 1);
	if (!command)
		return ;
	i = 0;
	while (str[i] != 32)
	{
		command[i] = str[i];
		i++;
	}
	command[i] = '\0';
	free(token->command);
	token->command = ft_find_path(command, main);
	free(command);
}

void	ft_strjoin_redir(char *f_part, char *line, t_token *token)
{
	int		start;
	int		end;
	int		x;
	char	*rtr;
	char	*tmp;

	end = ft_strlen(line);
	start = 0;
	x = 0;
	while (line[end - start] != '>')
		start++;
	while (line[end - start + x] != 32 && line[end - start + x])
		x++;
	tmp = ft_substr(line, (end - start), (start - x));
	rtr = ft_strjoin(f_part, tmp);
	free(tmp);
	ft_set_new_command(rtr, token, token->main);
	ft_set_new_valus(token, rtr);
	free(rtr);
	if (!token->heredoc)
	{
		free(token->name_file);
		if (token->output)
			ft_search_redir(token, ">");
		else if (token->append)
			ft_search_redir(token, ">>");
	}
	ft_print_lst(token);
	ft_single_redir(token, token->main);
}

void	ft_execute_multi_redir(t_token *token)
{
	char	**matrix;
	char	*tmp;
	int		i;

	i = 0;
	matrix = ft_split_original(token->main->copy_line, '>');
	while (matrix[++i])
	{
		tmp = ft_find_name_file(matrix[i]);
		open(tmp, O_CREAT | O_RDONLY, 0644);
		free(tmp);
	}
	matrix = ft_clear_matrix(matrix);
	tmp = (char *)malloc(sizeof(char) * 1);
	if (!tmp)
		return ;
	tmp[0] = '\0';
	i = 0;
	while (matrix[i])
		tmp = ft_strjoin(tmp, matrix[i++]);
	ft_free_matrix(matrix);
	ft_strjoin_redir(tmp, token->main->copy_line, token);
	free(tmp);
}
