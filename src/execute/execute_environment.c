/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/17 20:27:53 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_add_envi(char *var_add, t_main *main)
{
	int		i;
	char	**temp;

	i = 0;
	while (main->set_variables[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (NULL);
	i = -1;
	while (main->set_variables[++i])
	{
		temp[i] = ft_strdup(main->set_variables[i]);
		if (!temp[i])
			break ;
	}
	temp[i++] = ft_strdup(var_add);
	temp[i] = NULL;
	ft_free_matrix(main->set_variables);
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
	token->main->set_variables = ft_add_envi(var_add, token->main);
	// ft_store_matrix(token, token->main->set_variables);
	return (token->next);
}
