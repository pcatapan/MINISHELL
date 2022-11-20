/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:29:53 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/20 20:34:06 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_all(t_main *main)
{
	ft_free_matrix(main->copy_env);
	while (main->token)
	{
		free(main->token->command);
		ft_free_matrix(main->token->value);
		free(main->token->name_file);
		close(main->token->dup);
		close(main->token->stdinput);
		close(main->token->stdoutput);
		main->token = main->token->next;
	}
	while (main->token->prev)
	{
		free(main->token);
		if (!main->token->prev)
			break ;
		main->token = main->token->prev;
	}
	ft_free_matrix(main->export_env);
	free(main->files_pwd);
	free(main->copy_line);
	close(main->fd_export);
	close(main->fd_matrix);
}
