/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_easy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 00:26:30 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_path(t_main *main)
{
	int		i;
	char	*tmp;

	i = 0;
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0)
		{
			tmp = getcwd(NULL, 0);
			free(main->copy_env[i]);
			main->copy_env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	ft_cd(t_token *token, t_main *main)
{
	if (token->value[1] == NULL)
	{
		chdir(getenv("HOME"));
		cd_path(main);
	}
	else if (chdir(token->value[1]) == -1)
	{
		ft_printf(RED"cd: " ERROR_FILE COLOR_RES, token->value[1]);
		ft_printf("\n");
	}
	else
		cd_path(main);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
}

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	printf("nostro\n");
	while (main->copy_env[i])
	{
		ft_printf("%s\n", main->copy_env[i]);
		i++;
	}
}

void	ft_unset(t_token *token, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = 0;
		while (main->copy_env[j])
		{
			if (ft_strncmp(token->value[i], main->copy_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(main->copy_env[j]);
				main->copy_env[j] = NULL;
				while (main->copy_env[j + 1])
				{
					main->copy_env[j] = main->copy_env[j + 1];
					j++;
				}
				main->copy_env[j] = NULL;
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
	printf(RED "\texit\n" COLOR_RES);
	exit(3);
}
