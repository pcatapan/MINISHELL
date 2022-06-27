/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:33:11 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/27 03:29:30 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Inrase of one the SHLVL
 * 
 * @param copy_envp Where save the date, the copy of envp
 * @param num_str 	The number of SHLVL
 * @param index 	Position of SHLVL
 */
void	ft_change_shlvl(char **copy_envp, char *str, int index)
{
	int		num;
	char	*num_str;

	num = 0 + (str[6] - '0');
	num_str = ft_itoa(num + 1);
	copy_envp[index] = ft_strjoin("SHLVL=", num_str);
	free(num_str);
}

/**
 * @brief Copy all parameter of variable envp
 * 
 * @param copy_envp 	The copy of envp, where save the date
 * @param envp			The original envp
 */
void	ft_init_envp(char ***copy_envp, char **envp)
{
	int	i;
	char	*tmp;

	i = 0;
	while (envp[i])
		i++;
	*copy_envp = malloc(sizeof(char *) * (i + 2));
	if (!copy_envp)
		return ;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("SHLVL=", envp[i], 6))
			ft_change_shlvl((*copy_envp), envp[i], i);
		else if (!ft_strncmp("SHELL=", envp[i], 5))
			(*copy_envp)[i] = ft_strdup("SHELL=42minishell");
		else
		{
			(*copy_envp)[i] = ft_strdup(envp[i]);
			if ((*copy_envp)[i])
				continue;
			ft_free_copy_env(*copy_envp);
			exit(write(1, "Error setting up env\n", 21));
		}				
	}
	(*copy_envp)[i++] = ft_strdup("HISTSIZE=2000");
	tmp = ft_searchstrchr("HOME=", envp);
	(*copy_envp)[i++] = ft_strjoin(tmp, FILE_HISTORY);
	free(tmp);
	(*copy_envp)[i] = NULL;
}
