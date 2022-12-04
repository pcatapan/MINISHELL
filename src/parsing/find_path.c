/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 04:45:34 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 17:29:58 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_exceptions_path(t_main *main)
{
	int	len;
	int	i;

	i = 0;
	len = ft_matrixlen(main->copy_env);
	while (main->copy_env[i])
	{
		if (!(ft_strncmp("PATH=", main->copy_env[i], 5)))
			break ;
		i++;
	}
	if (i >= len)
	{
		g_exit = 127;
		return (1);
	}
	return (i);
}

static char	*ft_support_path(char *cmd, char *paths)
{
	char	*rtr;
	char	*part_path;

	part_path = ft_strjoin(paths, "/");
	rtr = ft_strjoin(part_path, cmd);
	free(part_path);
	return (rtr);
}

char	*ft_find_path(char *cmd, t_main *main)
{
	char	**paths;
	char	*right_path;
	int		i;

	i = ft_exceptions_path(main);
	if (i == 1)
		return (NULL);
	if (ft_strnstr(cmd, "/bin/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	paths = ft_split(main->copy_env[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		right_path = ft_support_path(cmd, paths[i]);
		if (access(right_path, F_OK) == 0)
		{
			ft_free_matrix(paths);
			return (right_path);
		}
		free(right_path);
	}
	ft_free_matrix(paths);
	return (NULL);
}
