/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:56:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/28 21:40:01 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_find_token(char *line, t_main *main, bool first)
{
	int		start;
	char	*command;
	char	*rtr;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ' || line[start] == '(')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	command = ft_substr(line, start, end);
	if (first)
	{
		free(main->token);
		main->token = ft_lstnew(command, main);
	}
	else
		ft_lstadd_back(&main->token, ft_lstnew(command, main));
	free(command);
	rtr = ft_substr(line, start + end, ft_strlen(line));
	return (rtr);
}
