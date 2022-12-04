/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:59:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 18:24:49 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_brackets(char *line, t_main *main)
{
	int	i;

	i = -1;
	main->open_brackets = 0;
	main->close_brackets = 0;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == '(')
			main->open_brackets++;
		if (line[i] == ')')
		main->close_brackets++;
	}
	if (main->open_brackets > main->close_brackets)
	{
		main->error = TRUE;
		ft_putendl_fd(RED ERROR_OPEN_BRACKETS COLOR_RES, STDOUT_FILENO);
	}
	else if (main->open_brackets < main->close_brackets)
	{
		main->error = TRUE;
		ft_putendl_fd(RED ERROR_CLOSE_BRACKETS COLOR_RES, STDOUT_FILENO);
	}
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

void	ft_check_operetor_logic(char *line, t_main *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == '&' || line[i] == '|')
		{
			if (line[i + 1] == '&' && line[i + 2] != '&')
				i++;
			else if ((line[i + 1] == '|' || line[i + 1] != '|') \
					&& line[i + 2] != '|' && line[i] != '&')
				i++;
			else
			{
				ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
				main->error = true;
				break ;
			}
		}
		i++;
	}
}

void	ft_check_syntax(char *line, t_main *main)
{
	main->error = false;
	main->dub_quotes = 0;
	main->sin_quotes = 0;
	main->redirections = false;
	main->expand = false;
	ft_easy_synatx(line, main);
	if (ft_strchr(line, '$') && !main->error)
		main->error = ft_expand_check(line);
	if (!main->error)
		ft_check_redirection(line, main);
	if (!main->error)
		ft_check_operetor_logic(line, main);
	if (main->op_logic && !main->error)
		ft_check_brackets(line, main);
	if (main->error == TRUE)
		g_exit = 258;
}
