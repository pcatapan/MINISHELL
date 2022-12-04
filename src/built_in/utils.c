/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:32:54 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 18:03:15 by pcatapan         ###   ########.fr       */
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
		if (ft_strncmp(matrix[i], str, (ft_strlen(str))) == 0)
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

char	*ft_check_echo_n(char *str)
{
	size_t		i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (i < ft_strlen(str))
		return (str);
	else
		return ("-n");
}
