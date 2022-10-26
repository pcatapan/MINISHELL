/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 16:57:46 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_add_envi(char *var_add, t_main *main)
{
	int		i;
	char	**temp;

	i = 0;
	while (main->copy_env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (NULL);
	i = -1;
	while (main->copy_env[++i])
	{
		temp[i] = ft_strdup(main->copy_env[i]);
		if (!temp[i])
			break ;
	}
	temp[i++] = ft_strdup(var_add);
	temp[i] = NULL;
	ft_free_matrix(main->copy_env);
	//free(var_add);
	return (temp);
}

int	ft_check_envi(char *line)
{
	int	i;

	i = 1;
	if (ft_isalpha(line[0]) == 0)
		return (0);
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
	// ft_store_matrix(token, token->main->set_variables);
	if (token->next)
		token = token->next;
	return (token);
}
