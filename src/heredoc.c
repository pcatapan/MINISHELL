/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/14 15:32:22 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    ft_write_fd(int fd, char *limitor, t_main *main)
{
	char	*str;

	while (1)
	{
		if (ft_strchr(str, '"') == 0)
			main->expand = 1;
		str = readline("> ");
		//eliminare "" dal limitor
		//in base se ce o meno eseguire l'expand dollar o meno
		if (ft_strcmp(limitor, str) == 1)
			break;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
}


int	ft_heredoc(t_token *token, t_main *main)
{
	int fd;
	char *name_file = "heredoc";
	
	fd = open (name_file, O_CREAT | O_EXCL | O_RDWR);
	ft_write_fd(fd, token->next->value[0], main);
	// fd = open (name_file, O_RDONLY);
	return (fd);
}
