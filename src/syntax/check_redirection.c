/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:32:21 by aanghel           #+#    #+#             */
/*   Updated: 2022/12/03 19:52:09 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief The funcion check the redirecion
 * 
 * @param line Str in to find the redirection
 * @param i Position of str in to find
 * @return int Return 0 isn't find and 1 is find
 */
int	ft_check_redir_char(char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<' && line[i - 1] != '<')
			return (1);
		else
			return (1);
	}
	if (line[i] == '>')
	{
		if (line[i + 1] == '>' && line[i - 1] != '>')
			return (1);
		else
			return (1);
	}
	return (0);
}

void	ft_check_redirection(char *line, t_main *main)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if ((line[i] == OUTPUT && line[i + 1] == INPUT) || \
			(line[i] == INPUT && line[i + 1] == OUTPUT) || \
			(line[i] == INPUT && line[i + 1] == INPUT && line[i - 1] == INPUT) \
			|| (line[i] == OUTPUT && line[i + 1] == OUTPUT
				&& line[i - 1] == OUTPUT))
			main->error = true;
		if (line[i] == INPUT)
			main->redirections = true;
		if (line[i] == OUTPUT)
			main->redirections = true;
	}
	if (main->error)
		ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
}
