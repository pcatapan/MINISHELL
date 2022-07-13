/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/06 17:13:42 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_add_envi(char *line, t_main *main)
{
	int		i;
	char	**temp;

	i = 0;
	while (main->copy_env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (NULL);
	i = -1;
	while (main->copy_env[++i])
	{
		temp[i] = ft_strdup(main->copy_env[i]);
		if (!temp[i])
			break ;
	}
	temp[i++] = ft_strdup(line);
	temp[i] = NULL;
	ft_free_matrix(main->copy_env);
	free(line);
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