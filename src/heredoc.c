/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 18:02:57 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 15:33:50 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//main->expand == false -> no expand dollar
//main->expand == true -> expand dollar

int	ft_write_fd(int fd, char *limiter, t_main *main)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (ft_strchr(limiter, '"') == 0)
			main->expand = true;
		if (main->expand == true)
		{
			if (ft_strchr(str, '$') == 1)
				str = ft_expand_heredoc(str, main);
		}
		if (ft_strcmp(limiter, str) == 1)
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free(str);
	return (0);
}

int	ft_heredoc(t_token *token, t_main *main)
{
	int		fd;
	char	*name_file;

	name_file = "heredoc";
	fd = open (name_file, O_CREAT | O_EXCL | O_WRONLY, 0644);
	ft_write_fd(fd, token->value[2], main);
	fd = open (name_file, O_RDONLY);
	return (fd);
}