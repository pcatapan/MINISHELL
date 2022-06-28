/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:53:41 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/28 23:19:02 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_history(char *line, char **envp)
{
	int		fd;
	int		flag_file;
	char	*path;
	char	*tmp;

	flag_file = O_APPEND | O_WRONLY | O_CREAT;
	tmp = ft_searchstrchr("PWD=", envp);
	//path = ft_strjoin(ft_searchstrchr("HOME=", envp), FILE_HISTORY);
	path = ft_strjoin(tmp, "/42minishell_history");
	free(tmp);
	fd = open(path, flag_file, S_IRWXU | S_IRGRP | S_IROTH);
	free(path);
	if (fd < 0)
		return ;
	ft_putendl_fd(line, fd);
	close(fd);
	add_history(line);
}
