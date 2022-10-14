/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/14 18:41:48 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    ft_write_fd(int fd, char *limiter, t_main *main)
{
	char	*str;

	while (1)
	{
		if (ft_strchr(str, '"') == 0)
			main->expand = true;
		//eliminare le double quote dal limiter
		if (ft_strcmp(limiter, str) == 1)
			break;
		str = readline("> ");
		//main->expand == false -> expand dollar
		//main->expand == true -> no expand dollar
		//capire come integrare ft_expand_dollar in questo caso
		// if (main->expand == false)
		// 	str = ft_expand_dollar(str, main);
		if (main->expand == true)
			str = ft_no_exp(str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	return (0);
}


int	ft_heredoc(t_token *token, t_main *main)
{
	int fd;
	char *name_file = "heredoc";
	
	fd = open (name_file, O_CREAT | O_EXCL | O_RDWR);
	ft_write_fd(fd, token->next->value[0], main);
	fd = open (name_file, O_RDONLY);
	return (fd);
}
