/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:43:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 14:32:59 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute_dollar(t_token *token)
{
	int		i;
	char	*tmp;
	bool	res;

	i = 0;
	res = FALSE;
	while (token->value[i])
	{
		if (ft_strchr(token->value[i], '$'))
			res = TRUE;
		if (res)
		{
			tmp = ft_expand_dollar(token->value[i], token->main);
			token->value[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
}

t_token	*ft_end_execute_(t_token *token, int fd_pipe[2], t_main *main)
{
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
		token->dup = token->prev->dup;
	}
	if (token->prev && token->prev->pipe && token->stdinput == STDIN_FILENO)
	{
		token->dup = dup(STDIN_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		token->stdinput = fd_pipe[0];
		close(fd_pipe[0]);
	}
	else if (token->stdinput != token->dup)
		dup2(token->dup, STDIN_FILENO);
	ft_free_matrix(main->copy_env);
	ft_free_matrix(main->export_env);
	main->copy_env = ft_get_next_line(main->fd_matrix,
			ft_strjoin(main->files_pwd, "irina"));
	main->export_env = ft_get_next_line(main->fd_export,
			ft_strjoin(main->files_pwd, "export"));
	return (token);
}

void	ft_store_matrix(t_main *main)
{
	int		i;

	i = 0;
	while (main->copy_env[i])
	{
		write(main->fd_matrix, main->copy_env[i], ft_strlen(main->copy_env[i]));
		write(main->fd_matrix, "\n", 1);
		i++;
	}
	close(main->fd_matrix);
	i = 0;
	while (main->export_env[i])
	{
		write(main->fd_export, main->export_env[i],
			ft_strlen(main->export_env[i]));
		write(main->fd_export, "\n", 1);
		i++;
	}
	close(main->fd_export);
}
