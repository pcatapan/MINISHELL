/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 23:38:30 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_support_strjoin_redir(t_token *token)
{
	if (!token->heredoc)
	{
		free(token->name_file);
		token->name_file = NULL;
		if (token->output)
			ft_search_redir(token, ">");
		else if (token->append)
			ft_search_redir(token, ">>");
	}
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
	char	*rtr;
	char	*tmp;

	end = ft_strlen(line);
	start = 0;
	while (line[end - start] != '>')
		start++;
	tmp = ft_substr(line, (end - start), (start));
	f_part = ft_strcat(f_part, " ");
	rtr = ft_strjoin(f_part, tmp);
	free(tmp);
	ft_set_new_command(rtr, token, token->main);
	ft_set_new_valus(token, rtr);
	free(rtr);
	ft_support_strjoin_redir(token);
	ft_single_redir(token, token->main);
}

void	ft_execute_multi_redir(t_token *token)
{
	char	**matrix;
	char	*rtr;
	int		i;

	i = 0;
	matrix = ft_split_original(token->main->copy_line, '>');
	while (matrix[++i])
	{
		rtr = ft_find_name_file(matrix[i]);
		open(rtr, O_CREAT | O_RDONLY, 0644);
		free(rtr);
	}
	matrix = ft_clear_matrix(matrix);
	rtr = (char *)malloc(sizeof(char) * 1);
	if (!rtr)
		return ;
	rtr[0] = '\0';
	i = 0;
	while (matrix[i])
		rtr = ft_strjoin(rtr, matrix[i++]);
	ft_free_matrix(matrix);
	ft_strjoin_redir(rtr, token->main->copy_line, token);
	free(rtr);
}
