/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_easier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:50:21 by fgrossi           #+#    #+#             */
/*   Updated: 2022/11/27 05:09:14 by pcatapan         ###   ########.fr       */
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
			printf("TMP2 :%s\n", tmp);
			printf("line Env :%s\n", main->copy_env[i]);
			free(main->copy_env[i]);
			main->copy_env[i] = ft_strjoin("PWD=", tmp);
			printf("line Env 2:%s\n", main->copy_env[i]);
			free(tmp);
		}
		i++;
	}
}

void	ft_cd(t_token *token, t_main *main)
{
	char	*tmp;

	if (token->value[1] == NULL)
	{
		tmp = getenv("HOME");
		printf("%s\n", tmp);
		chdir(tmp);
		cd_path(main);
	}
	else if (chdir(token->value[1]) == -1)
	{
		g_exit = 1;
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
	free(pwd);
}

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	while (main->copy_env[i])
	{
		ft_printf("%s\n", main->copy_env[i]);
		i++;
	}
}
