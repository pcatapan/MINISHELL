/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:44:10 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 15:49:05 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Free the matrix
 * 
 * @param matrix is the matrix to free
 */
void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	ft_free_token(t_token *token)
{
	token = ft_return_head(token);
	while (token)
	{
		if (token->command)
			free(token->command);
		ft_free_matrix(token->value);
		if (token->name_file)
			free(token->name_file);
		if (token->next)
			free(token);
		if (!token)
			break ;
		token = token->next;
	}
}

void	ft_free_main(t_main *main)
{
	// ft_free_matrix(main->copy_env);
	// free(main->token);
	// close(main->fd_export);
	// close(main->fd_matrix);
}
