/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:43:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 01:34:09 by pcatapan         ###   ########.fr       */
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

t_token	*ft_end_execute_(t_token *token, int fd_pipe[2])
{
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
	}
	if (token->prev && token->prev->pipe && token->stdinput == STDIN_FILENO)
	{
		token->dup = dup(STDIN_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		token->stdinput = fd_pipe[0];
		close(fd_pipe[0]);
		printf("Fake :%d --- Ori: %d\n", token->stdinput, STDIN_FILENO);
	}
	else if (token->stdinput != STDIN_FILENO)
	{
		dup2(token->dup, STDIN_FILENO);
		printf("Entro --- Dup: %d\n", token->dup);
	}
	return (token);
}

void	ft_store_matrix(t_token *token, char **matrix)
{
	int	i;

	i = 0;
	// dup2(token->fd_mini[1], STDOUT_FILENO);
	// printf("%d\n", token->fd_mini[1]);
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	dup2(token->stdoutput, STDOUT_FILENO);
}
