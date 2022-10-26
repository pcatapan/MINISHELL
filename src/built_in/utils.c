/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:32:54 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 15:57:19 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_builtin(t_token *token)
{
	if (ft_strcmp(token->value[0], "exit") || ft_strcmp(token->value[0], "env") \
	|| ft_strcmp(token->value[0], "unset") || ft_strcmp(token->value[0], "pwd") \
	|| ft_strcmp(token->value[0], "cd") || ft_strcmp(token->value[0], "echo") \
	|| ft_strcmp(token->value[0], "export"))
		return (1);
	return (0);
}

t_token	*ft_end_execute_(t_token *token, int fd_pipe[2])
{
	if (token->next)
		token = token->next;
	// else
	// 	token->res = read(fd[0], buffer, 42);
	// free(buffer);
	if (token->prev && token->prev->pipe && token->stdinput == STDIN_FILENO)
	{
		token->dup = dup(STDIN_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		token->stdinput = fd_pipe[0];
	}
	else if (token->stdinput != STDIN_FILENO)
		dup2(token->dup, STDIN_FILENO);
	return (token);
}
