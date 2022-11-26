/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:53:41 by pcatapan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/24 02:25:02 by aanghel          ###   ########.fr       */
=======
/*   Updated: 2022/11/19 17:49:16 by fgrossi          ###   ########.fr       */
>>>>>>> parent of 823e986... fix primi leaks
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_history(char *line, char **envp)
{
	int		fd;
	char	*path;
	char	*tmp;

	tmp = ft_searchstrchr("HOME=", envp);
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
