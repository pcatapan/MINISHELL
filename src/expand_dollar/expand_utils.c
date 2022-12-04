/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 01:21:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 01:21:44 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_support(char *line, int i, bool error)
{
	if (line[++i] == '{')
	{
		while (line[++i] != 32 && line[i])
		{
			if (line[i] == '}')
			{
				error = FALSE;
				break ;
			}
		}
	}
	else
		error = FALSE;
	return (error);
}

bool	ft_expand_check(char *line)
{
	int		i;
	bool	error;

	i = 0;
	error = TRUE;
	while (line[i] != '$')
		i++;
	error = ft_support(line, i, error);
	if (error)
	{
		ft_putendl_fd(RED ERROR_CLOSE_ COLOR_RES, STDOUT_FILENO);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_execute_dollar(t_token *token, t_main *main)
{
	int		i;
	int		j;
	int		doub_quot;

	i = 0;
	j = 0;
	doub_quot = 0;
	while (token->value[i])
	{
		j = 0;
		while (token->value[i][j])
		{
			if (token->value[i][j] == '"')
				doub_quot++;
			if (doub_quot % 2 == 0)
				j = ft_check_single_quote(token->value[i], main, j);
			if (ft_check_expand(token->value[i], j))
				token->value[i] = ft_expand_doll(token->value[i], main, j + 1);
			j++;
		}
		i++;
	}
}

char	*ft_expand_heredoc(char *line, t_main *main)
{
	int	i;
	int	l;
	int	start;

	i = 0;
	l = 0;
	start = 0;
	while (line[i] != '$' )
		i++;
	if (line[i] == '$')
		start = i + 1;
	while (line[++i] && line[i] != ' ' && line[i] != '"')
		l++;
	if (start != 0)
		line = ft_change_var_in_dollar(start, l, line, main);
	return (line);
}
