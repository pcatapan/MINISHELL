/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:44:10 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/24 03:32:07 by aanghel          ###   ########.fr       */
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
	while (token)
	{
		free(token->command);
		ft_free_matrix(token->value);
		free(token->name_file);
		if (!token)
			break ;
		token = token->next;
	}
}

void	ft_free_main(t_main *main)
{
	ft_free_matrix(main->copy_env);
	free(main->token->main);
	free(main->token);
	free(main->copy_line);
	close(main->fd_export);
	close(main->fd_matrix);
	free(main);
}