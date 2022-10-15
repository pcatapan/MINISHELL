/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:56:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/15 19:25:33 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_find_token(char *line, t_main *main)
{
	int		start;
	char	*command;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ' || line[start] == '(')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	command = ft_substr(line, start, end);
	if (!main->token)
		main->token = ft_lstnew(command, main);
	else
		ft_lstadd_back(&main->token, ft_lstnew(command, main));
	//free(command);
	return (&line[start + end]);
}
