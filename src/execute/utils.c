/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:43:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/16 20:05:31 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute_dollar(t_token *token)
{
	int		i;
	char	*tmp;
	bool	res;

	i = 0;
	res = FALSE;
	while (token->value[i])
	{
		if (ft_strchr(token->value[i], '$'))
			res = TRUE;
		if (res)
		{
			tmp = ft_expand_dollar(token->value[i], token->main);
			token->value[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
}

void	ft_print_matrix(t_token *token)
{
	int	i;

	i = 0;
	dup2(token->fd_mini[1], STDOUT_FILENO);
	printf("%d\n", token->fd_mini[1]);
	while (token->main->copy_env[i])
	{
		printf("%s\n", token->main->copy_env[i]);
		i++;
	}
	dup2(token->stdoutpt, STDOUT_FILENO);
}
