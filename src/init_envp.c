/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:33:11 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 05:15:20 by pcatapan         ###   ########.fr       */
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

void	ft_add_shell_env(char **copy_envp, char **envp, int i)
{
	char	*tmp;
	char	*tmp2;

	copy_envp[i++] = ft_strdup("HISTSIZE=2000");
	tmp = ft_searchstrchr("HOME=", envp);
	tmp2 = ft_strjoin("HISTFILE=", tmp);
	copy_envp[i++] = ft_strjoin(tmp2, FILE_HISTORY);
	free(tmp);
	free(tmp2);
	copy_envp[i] = NULL;
}

/**
 * @brief Copy all parameter of variable envp
 * 
 * @param envp			The original envp
 * @return copy_envp 	The copy of envp, where save the date
 */
char	**ft_init_envp(char **envp)
{
	int		i;
	char	**copy_envp;

	i = 0;
	while (envp[i])
		i++;
	copy_envp = malloc(sizeof(char *) * (i + 3));
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("SHLVL=", envp[i], 6))
			ft_change_shlvl(copy_envp, envp[i], i);
		else if (!ft_strncmp("SHELL=", envp[i], 5))
			copy_envp[i] = ft_strdup("SHELL=42minishell");
		else
		{
			copy_envp[i] = ft_strdup(envp[i]);
			if (copy_envp[i])
				continue ;
			ft_free_matrix(copy_envp);
			exit(write(1, "Error setting up env\n", 21));
		}				
	}
	ft_add_shell_env(copy_envp, envp, i);
	return (copy_envp);
}
