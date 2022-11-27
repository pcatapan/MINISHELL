/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 03:26:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/26 22:21:44 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_create_line(t_token *token)
{
	char	*tmp;
	char	*val;
	int		i;

	tmp = (char *)malloc(sizeof(char) * 1);
	if (!tmp)
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

char	**ft_clear_matrix(char **matrix)
{
	int		i;
	char	*tmp;

	i = 1;
	while (matrix[i])
	{
		tmp = ft_strdup(matrix[i]);
		free(matrix[i]);
		matrix[i++] = ft_strclear(tmp, 127);
		free(tmp);
	}
	return (matrix);
}

int	ft_count_redir_value(t_token *token)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (token->value[i])
	{
		j = 0;
		while (token->value[i][j])
		{
			if (token->value[i][j] == 62 || token->value[i][j] == 60)
				count++;
			j++;
		}
		if (count > 1)
			break ;
		i++;
	}
	return (count);
}
