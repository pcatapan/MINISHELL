/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:59:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/07 13:34:12 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_double_quote(char *line, t_main *main, int i)
{
	if (line[i] == '"')
	{
		main->dub_quotes++;
		i++;
		while (line[i])
		{
			if (line[i] == '"' && line[i - 1] != 92)
			{
				main->dub_quotes++;
				i++;
				break ;
			}
			i++;
		}
	}
	return (i);
}

int	ft_check_single_quote(char *line, t_main *main, int i)
{
	if (line[i] == 39)
	{
		main->sin_quotes++;
		i++;
		while (line[i])
		{
			if (line[i] == 39)
			{
				main->sin_quotes++;
				i++;
				break ;
			}
			i++;
		}
	}
	return (i);
}

int	ft_check_brackets(char *line, t_main *main)
{
	int	i;

	i = 0;
	main->open_brackets = 0;
	main->close_brackets = 0;
	while (line[i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == '(')
			main->open_brackets++;
		if (line[i] == ')')
		main->close_brackets++;
		i++;
	}
	if (main->open_brackets > main->close_brackets)
		ft_putendl_fd(RED ERROR_OPEN_BRACKETS COLOR_RES, STDOUT_FILENO);
	else if (main->open_brackets < main->close_brackets)
		ft_putendl_fd(RED ERROR_CLOSE_BRACKETS COLOR_RES, STDOUT_FILENO);
	return (i);
}

void	ft_easy_synatx(char *line, t_main *main)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		if (main->dub_quotes % 2 != 0 && !main->error)
		{
			ft_putendl_fd(RED ERROR_DOUBLE_QUOTE COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		i = ft_check_single_quote(line, main, i);
		if (main->sin_quotes % 2 != 0 && !main->error)
		{
			ft_putendl_fd(RED ERROR_SING_QUOTE COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		if (line[i] == 92 && line[i] && !main->error)
		{
			ft_putendl_fd(RED ERROR_BACKSLASH COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		if ((line[i] == 124 || line[i] == 38) && line[i])
			main->op_logic = true;
	}
}

void	ft_check_syntax(char *line, t_main *main)
{
	main->error = false;
	main->dub_quotes = 0;
	main->sin_quotes = 0;
	ft_easy_synatx(line, main);
	if (main->op_logic && !main->error)
		ft_check_brackets(line, main);
	if (ft_strchr(line, '=') == 1 && ft_check_envi(line) == 1)
		main->copy_env = ft_add_envi(line, main);
}
