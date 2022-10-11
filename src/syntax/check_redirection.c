/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:32:21 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/11 22:01:56 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_check_redirection(char *line, t_main *main)
{
	int i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if ((line[i] == OUTPUT && line[i + 1] == INPUT) || \
			(line[i] == INPUT && line[i + 1] == OUTPUT))
			break;
		if (line[i] == INPUT && line[i + 1] != INPUT)
			main->redirections = true;
		if (line[i] == INPUT && line[i + 1] == INPUT)
			main->redirections = true;
		if (line[i] == OUTPUT && line[i + 1] != OUTPUT)
			main->redirections = true;
		if (line[i] == OUTPUT && line[i + 1] == OUTPUT)
			main->redirections = true;
	}
	if (main->redirections == false)
	{
		ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
		main->error = true;
	}
}