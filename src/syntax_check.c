/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:59:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/30 17:42:31 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Aggiungere controllo sul '\'
int	ft_check_double_quote(char *line, t_main *main)
{
	int	i;

	i = 0;
	main->quotes = 0;
	while (line[i] && line)
	{
		if (line[i] == '"')
			main->quotes++;
		i++;
	}
	return (i);
}

int	ft_check_single_quote(char *line, t_main *main)
{
	int	i;

	i = 0;
	main->quotes = 0;
	while (line[i] && line)
	{
		if (line[i] == 39)
			main->quotes++;
		i++;
	}
	return (i);
}

void	check_syntax(char *line, t_main *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i = ft_check_double_quote(line, main);
			if (main->quotes % 2 != 0)
				ft_putendl_fd(ERROR_DOUBLE_QUOTE, STDOUT_FILENO);
		}
		else if (line[i] == 39)
		{
			i = ft_check_single_quote(line, main);
			if (main->quotes % 2 != 0)
				ft_putendl_fd(ERROR_SINGLE_QUOTE, STDOUT_FILENO);
		}
		i++;
	}
	if (ft_strchr(line, '=') == 1 && ft_check_envi(line) == 1)
		main->copy_env = ft_add_envi(line, main);
}
