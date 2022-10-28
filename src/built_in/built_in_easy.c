/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 19:04:08 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_token *token)
{
	char	*tmp;
	int		i;

	i = 0;
	if (token->value[1] == NULL)
		return ;
	if (chdir(token->value[1]) == -1)
		ft_printf(RED"cd: \n" ERROR_FILE COLOR_RES, token->value[1]);
	else
	{
		chdir(token->value[1]);
		while (token->main->copy_env[i])
		{
			if (ft_strncmp(token->main->copy_env[i], "PWD=", 4) == 0)
			{
				tmp = getcwd(NULL, 0);
				free(token->main->copy_env[i]);
				token->main->copy_env[i] = ft_strjoin("PWD=", tmp);
				free(tmp);
			}
			i++;
		}
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
}

void	ft_env(t_token *token)
{
	int	i;

	i = 0;
	printf("nostro\n");
	while (token->main->copy_env[i])
	{
		ft_printf("%s\n", token->main->copy_env[i]);
		i++;
	}
}

void	ft_unset(t_token *token)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = 0;
		while (token->main->copy_env[j])
		{
			if (ft_strncmp(token->value[i], token->main->copy_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(token->main->copy_env[j]);
				token->main->copy_env[j] = NULL;
				while (token->main->copy_env[j + 1])
				{
					token->main->copy_env[j] = token->main->copy_env[j + 1];
					j++;
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_exit(t_token *token)
{
	int	i;

	i = 0;
	while (token->main->copy_env[i])
	{
		free(token->main->copy_env[i]);
		i++;
	}
	free(token->main->copy_env);
	exit(0);
}
