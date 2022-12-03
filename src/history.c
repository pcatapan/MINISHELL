/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:53:41 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 20:00:18 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_history(char *line)
{
	int		fd;
	char	*path;
	char	*tmp;

	tmp = getenv("HOME");
	path = ft_strjoin(tmp, FILE_HISTORY);
	fd = open(path, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	free(path);
	add_history(line);
	if (fd < 0)
		return ;
	ft_putendl_fd(line, fd);
	close(fd);
}
