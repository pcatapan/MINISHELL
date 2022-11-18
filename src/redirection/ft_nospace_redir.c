/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nospace_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:10 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/16 00:54:37 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_del_line(char *line, char c, int i)
{
	if (c == 60)
	{
		while (line[i])
		{
			if (line[i] == '<')
				break ;
			i++;
		}
		while (line[i])
			line[i++] = 127;
	}
	else
	{
		while (line[i])
		{
			if (line[i] == '>')
				break ;
			i++;
		}
		while (line[i])
			line[i++] = 127;
	}
	return (line);
}

char	**ft_split_matrix(char **matrix, char c)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{	
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == c)
				matrix[i] = ft_del_line(matrix[i], c, j);
			j++;
		}
	}
	i = -1;
	while (matrix[++i])
		matrix[i] = ft_strclear(matrix[i], 127);
	i = -1;
	while (matrix[++i])
		if (ft_strcmp(matrix[i], "\0"))
			matrix[i] = matrix[i + 1];
	matrix[i] = NULL;
	return (matrix);
}

void	ft_final_line(t_token *token, char *line)
{
	int		end;
	int		start;
	char	dir;

	dir = '\0';
	end = ft_strlen(line);
	while (line[--end] >= 0)
	{
		if (line[end] == '<' || line[end] == '>')
		{
			dir = line[end];
			break ;
		}
	}
	end = ft_strlen(line);
	start = 0;
	while (line[end - start] != dir)
		start++;
	end = end - start + 1;
	while (line[--end])
		line[end] = 127;
	line = ft_strclear(line, 127);
	ft_new_token(token, line, dir);
}

void	ft_create_file(char **f_create, char **f_open, \
						t_token *token, char *line)
{
	int		i;
	int		fd;

	i = -1;
	while (f_create[++i])
	{
		fd = open (f_create[i], O_RDONLY, 0644);
		if (fd == -1)
			open (f_create[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	i = -1;
	while (f_open[++i])
	{
		fd = open (f_open[i], O_RDONLY, 0644);
		if (fd == -1)
		{
			printf(RED ERROR_FILE ": %s\n" COLOR_RES, f_open[i]);
			write(fd, "1", 1);
			exit(0);
		}
	}
	ft_final_line(token, line);
}

void	ft_multi_no_space(t_token *token)
{
	int		i;
	int		x;
	char	**file_create;
	char	**file_open;
	char	*line;

	x = -1;
	while (token->value[++x])
	{
		if (ft_strchr(token->value[x], '>') || ft_strchr(token->value[x], '<'))
			break ;
	}
	i = -1;
	while (token->value[++i])
	{
		if (ft_strchr(token->value[i], '<'))
			file_open = ft_split_original(token->value[i], '<');
		if (ft_strchr(token->value[i], '>'))
			file_create = ft_split_original(token->value[i], '>');
	}
	file_create = ft_split_matrix(file_create, '<');
	file_open = ft_split_matrix(file_open, '>');
	line = ft_strdup(token->value[x]);
	ft_create_file(file_create, file_open, token, line);
}
