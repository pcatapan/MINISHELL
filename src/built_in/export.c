/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/14 15:29:08 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_naked(t_token *token)
{
	int	i;

	i = 0;
	while (token->main->copy_env[i])
	{
		printf("declare -x %s\n", token->main->copy_env[i]);
		i++;
	}
	i = 0;
	while (token->main->export_env[i])
	{
		printf("declare -x %s\n", token->main->export_env[i]);
		i++;
	}
}

void	ft_add_to_env(t_token *token, char *var_add)
{
	int	j;

	if (ft_find_in_env(token->main->copy_env, var_add) != 0)
				j = ft_find_in_env(token->main->copy_env, var_add);
	else
	{
		j = ft_matrixlen(token->main->copy_env);
		token->main->copy_env[j + 1] = NULL;
	}
	free(token->main->copy_env[j]);
	token->main->copy_env[j] = ft_strdup(var_add);
}

void	ft_add_to_exp(t_token *token, char *var_add)
{
	int	j;

	if (ft_find_in_exp(token->main->export_env, var_add) != 0)
				j = ft_find_in_exp(token->main->export_env, var_add);
	else
	{
		j = ft_matrixlen(token->main->export_env);
		token->main->export_env[j + 1] = NULL;
	}
	free(token->main->export_env[j]);
	token->main->export_env[j] = ft_strdup(var_add);
	j = 0;
}

void	ft_export(t_token *token)
{
	int	i;

	i = 1;
	if (token->value[1] == NULL)
		return (ft_export_naked(token));
	while (token->value[i])
	{
		if (ft_strchr(token->value[i], '=') == 0
			|| ft_check_envi(token->value[i]) == 0)
		{
			if (ft_check_envi(token->value[i]) == 0)
				printf(RED"minishell: export: '%s': not a valid identifier\n"
					COLOR_RES, token->value[i]);
			else
				ft_add_to_exp(token, token->value[i]);
			i++;
			continue ;
		}
		ft_add_to_env(token, token->value[i]);
		i++;
	}
}
