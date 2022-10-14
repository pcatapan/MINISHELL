/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:25 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 00:16:23 by aanghel          ###   ########.fr       */
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
		str = readline("> ");
		//main->expand == false -> no expand dollar
		//main->expand == true -> expand dollar
		//capire come integrare ft_expand_dollar in questo caso
		// if (main->expand == true)
		// 	str = ft_expand(str);
		if (ft_strcmp(limiter, str) == 1)
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free(str);
	return (0);
}

// char	*ft_expand(char *line)
// {
// 	int	i;
// 	char	*new;

// 	i = 0;
// 	new = NULL;
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
		
// 		i++;
// 	}
// 	return (new);
// }

int	ft_heredoc(t_token *token, t_main *main)
{
	int fd;
	char *name_file = "heredoc";
	
	//trovare un modo per creare file per tutti i heredoc che si vuole, il nome è indifferente
	fd = open (name_file, O_CREAT | O_EXCL | O_WRONLY, 0644);
	ft_write_fd(fd, token->next->value[0], main);
	fd = open (name_file, O_RDONLY);
	return (fd);
}
