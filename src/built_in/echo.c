/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/27 00:49:54 by pcatapan         ###   ########.fr       */
=======
/*   Updated: 2022/11/20 20:14:38 by aanghel          ###   ########.fr       */
>>>>>>> parent of d679adb... fix primi leaks echo ciao
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_token *token)
{
	int		i;

	i = 1;
	if (ft_strcmp(token->value[1], "-n") != 0)
		i++;
	while (token->value[i])
	{	
		if (ft_strcmp(token->value[i], "$?"))
		{
			printf("%d ", g_exit);
			i++;
		}
		else
		{
			printf("%s", token->value[i]);
			if (token->value[i + 1])
				printf(" ");
			i++;
		}
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
				exit(0);
		}
		exit(1);
	}
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

void	ft_preparet_echo(t_token *token)
{
	int		i;
	int		j;

	i = -1;
	while (token->value[++i])
	{
		j = -1;
		while (token->value[i][++j])
		{
			if (token->value[i][j] == '\'')
				j = ft_oppost_trim(token->value[i], j, '"');
			else if (token->value[i][j] == '"')
				j = ft_oppost_trim(token->value[i], j, '\'');
		}
		token->value[i] = ft_strtrim2(token->value[i], 127);
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
			{
				if (token->priority == 0)
					ft_echo(token);
				exit(1);
			}
			ft_echo(token);
		}
		else
			ft_echo(token);
	}
	else
		ft_echo(token);
}
