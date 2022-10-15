/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/15 20:02:56 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_bultin(t_token *token)
{
	if (ft_strcmp(token->value[0], "exit") || ft_strcmp(token->value[0], "env") \
	|| ft_strcmp(token->value[0], "unset") || ft_strcmp(token->value[0], "pwd") \
	|| ft_strcmp(token->value[0], "cd") || ft_strcmp(token->value[0], "echo") \
	|| ft_strcmp(token->value[0], "export"))
		return (1);
	return (0);
}

t_token	*ft_execute_bultin(t_token *token)
{
	pid_t	pidchild;
	int		fd[2];

	pidchild = fork();
	if (pipe(fd) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	//Qui il processo che gesticse le esecuzioni si ferma
	if (pidchild != 0)
	{
		close(fd[1]);//Close Write
		waitpid(pidchild, 0, 0);
	}
	// Tutti i processi che entrano qui muoiono
	else
	{
		close(fd[0]);//Close Read
		if (ft_strcmp(token->value[0], "echo"))
			ft_echo(token, fd);
		// file_desc = open("test.txt", O_WRONLY | O_APPEND);
		// dup2(file_desc, STDOUT_FILENO);
	}
	if (token->next)
	{
		token = token->next;
		token->res = read(fd[0], "1", 1);
	}
	token->res = read(fd[0], "1", 1);
	return (token);
}
