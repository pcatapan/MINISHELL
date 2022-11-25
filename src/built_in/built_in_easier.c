/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_easier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:50:21 by fgrossi           #+#    #+#             */
/*   Updated: 2022/11/24 02:21:05 by aanghel          ###   ########.fr       */
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
			tmp = (char *)malloc(sizeof(char) * 256);
			if (!tmp)
				return ;
			getcwd(tmp, 256);
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

	pwd = (char *)malloc(sizeof(char) * 256);
	if (!pwd)
		return ;
	getcwd(pwd, 256);
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
