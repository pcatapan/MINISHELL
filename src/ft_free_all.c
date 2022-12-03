/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:29:53 by aanghel           #+#    #+#             */
/*   Updated: 2022/12/03 19:50:25 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_all(t_main *main)
{
	while (main->token)
	{
		free(main->token->command);
		ft_free_matrix(main->token->value);
		free(main->token->name_file);
		main->token = main->token->next;
	}
	free(main->token);
	free(main->copy_line);
	close(main->fd_export);
	close(main->fd_matrix);
}
