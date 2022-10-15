/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/15 20:02:01 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_token *token, int fd[2])
{
	if (execve(token->command, token->value, token->main->copy_env))
	{
		perror(RED"ERRORE1"COLOR_RES);
		write(fd[1], "1", 1);
		exit(0);
	}
}
