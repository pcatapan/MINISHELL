/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 23:27:48 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_token *token)
{
	int		i;

	i = 1;
	if (!token->value[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(token->value[1], "-n") != 0)
		i++;
	while (token->value[i])
	{	
		printf("%s", token->value[i]);
		if (token->value[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(token->value[1], "-n") == 0)
		printf("\n");
}

void	ft_echo_or(t_token *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				;
		}
	}
	else
		ft_echo(token);
}

static int	ft_oppost_trim(char *line, int i, char trim)
{
	char	quot;

	quot = line[i];
	if (ft_strchr(&line[i], trim))
		line[i] = 127;
	while (line[i] != quot)
		i++;
	if (line[i] == quot)
		line[i] = 127;
	return (i);
}

static void	ft_preparet_echo(t_token *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (token->value[++i])
	{
		j = -1;
		if (ft_strnstr(token->value[i], "-n", 2))
			token->value[i] = ft_check_echo_n(token->value[i]);
		while (token->value[i][++j])
		{
			if (token->value[i][j] == '\'')
				j = ft_oppost_trim(token->value[i], j, '"');
			else if (token->value[i][j] == '"')
				j = ft_oppost_trim(token->value[i], j, '\'');
		}
		tmp = ft_strtrim2(token->value[i], 127);
		token->value[i] = ft_strdup(tmp);
	}
}

void	ft_check_echo(t_token *token)
{
	ft_preparet_echo(token);
	if (token->prev)
	{
		if (token->prev->or)
			ft_echo_or(token);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_echo(token);
		}
		else
			ft_echo(token);
	}
	else
		ft_echo(token);
}
