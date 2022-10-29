/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:53:41 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 00:50:11 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_history(char *line, char **envp)
{
	int		fd;
	char	*path;
	char	*tmp;

	tmp = ft_searchstrchr("HOME=", envp);
	// path = ft_strjoin(ft_searchstrchr("HOME=", envp), FILE_HISTORY);
	path = ft_strjoin(tmp, FILE_HISTORY);
	free(tmp);
	fd = open(path, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	free(path);
	add_history(line);
	if (fd < 0)
		return ;
	ft_putendl_fd(line, fd);
	close(fd);
}
