/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:32:54 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 01:09:22 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_find_in_env(char **matrix, char *str)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, ft_strchr_until(str, '=')) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	ft_find_in_exp(char **matrix, char *str)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	ft_check_builtin(t_token *token)
{
	if (ft_strcmp(token->value[0], "exit") || ft_strcmp(token->value[0], "env") \
	|| ft_strcmp(token->value[0], "unset") || ft_strcmp(token->value[0], "pwd") \
	|| ft_strcmp(token->value[0], "cd") || ft_strcmp(token->value[0], "echo") \
	|| ft_strcmp(token->value[0], "export"))
		return (1);
	return (0);
}

char	*ft_clear_value(char *str)
{
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	if (str[0] == 34 || str[0] == 39)
		start = 1;
	while (str[i + start])
		i++;
	if (str[i] == 34 || str[i] == 39)
		end = i - 1;
	else
		end = ft_strlen(str);
	return (ft_substr(str, start, end));
}
