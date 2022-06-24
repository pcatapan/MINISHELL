/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:33:11 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/24 01:53:13 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_change_shlvl(char **copy_envp, char num_str, int index)
{
	int	num;

	num = 0 + (num_str - '0');
	num = num + 1;
	num_str = num + 48;
	copy_envp[index] = ft_strjoin("SHLVL=", &num_str);
}

void	ft_init_envp(char ***copy_envp, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	*copy_envp = malloc(sizeof(char *) * i);
	if (!copy_envp)
		return ;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("SHLVL=", envp[i], 6))
			ft_change_shlvl((*copy_envp), envp[i][6], i);
		else if (!ft_strncmp("SHELL=", envp[i], 5))
			(*copy_envp)[i] = ft_strdup("SHELL=42minishell");
		else
		{
			(*copy_envp)[i] = ft_strdup(envp[i]);
			if ((*copy_envp)[i])
				continue ;
			ft_free_copy_env((*copy_envp));
			exit(write(1, "Error setting up env\n", 21));
		}
	}
}