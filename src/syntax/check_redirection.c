/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:32:21 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 16:56:29 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_check_redirection(char *line, t_main *main)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if ((line[i] == OUTPUT && line[i + 1] == INPUT) || \
			(line[i] == INPUT && line[i + 1] == OUTPUT))
			main->error = true;
		if (line[i] == INPUT)
			main->redirections = true;
		if (line[i] == OUTPUT)
			main->redirections = true;
	}
	if (main->error)
		ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
}
