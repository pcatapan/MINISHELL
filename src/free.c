/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:44:10 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/26 18:39:53 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Free the matrix
 * 
 * @param copy_env is the matrix to free
 */
void	ft_free_copy_env(char **copy_env)
{
	int	i;

	i = 0;
	if (!copy_env)
		return ;
	while (copy_env[i])
	{
		free(copy_env[i]);
		i++;
	}
	free(copy_env);
}