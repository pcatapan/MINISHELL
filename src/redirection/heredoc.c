/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/13 00:00:14 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//main->expand == false -> no expand dollar
//main->expand == true -> expand dollar

int	ft_write_fd(int fd, char *limiter, t_main *main)
{
	char	*str;

	main->expand = ft_strchr(limiter, '"');
	limiter = ft_strtrim(limiter, "\"");
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(limiter, str) == 1)
			break ;
		if (main->expand == 0)
		{
			if (ft_strchr(str, '$') == 1)
				str = ft_expand_heredoc(str, main);
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free(str);
	return (0);
}

int	ft_heredoc(t_token *token, t_main *main)
{
	int		fd;
	int		start;
	char	*tmp;
	int		end;
	char	*n_file;

	n_file = ".heredoc";
	fd = open (n_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_write_fd(fd, token->name_file, main);
	fd = open (n_file, O_RDWR);
	dup2(fd, STDIN_FILENO);
	start = 0;
	end = 0;
	while (main->copy_line[start] != '>')
		start++;
	start += 2;
	while (main->copy_line[start + end] != 32 \
			&& main->copy_line[start + end])
		end++;
	tmp = ft_substr(main->copy_line, start, end);
	free(token->name_file);
	token->name_file = ft_strdup(tmp);
	free(tmp);
	return (fd);
}
