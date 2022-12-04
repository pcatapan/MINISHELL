/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/02 23:24:59 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**ft_add_envi(char *var_add, t_main *main)
{
	int		i;
	char	**tmp;

	i = 0;
	while (main->copy_env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	i = -1;
	while (main->copy_env[++i])
	{
		tmp[i] = ft_strdup(main->copy_env[i]);
		if (!tmp[i])
			break ;
	}
	tmp[i++] = ft_strdup(var_add);
	tmp[i] = NULL;
	ft_free_matrix(main->copy_env);
	return (tmp);
}

int	ft_check_envi(char *line)
{
	int	i;

	i = 1;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
		return (0);
	while (line[i] == '_')
		i++;
	while (line[i])
	{
		if (ft_isalnum(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

t_token	*ft_execute_enviroment(t_token *token, char *var_add)
{
	token->main->copy_env = ft_add_envi(var_add, token->main);
	if (token->next)
		token = token->next;
	return (token);
}
