/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:56:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/21 20:23:44 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_find_token(char *line, t_main *main)
{
	int		start;
	char	*command;
	char	*tmp;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ' || line[start] == '(')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	tmp = ft_substr(line, start, end);
	command = ft_strtrim2(tmp, '\"');
	if (!main->token)
		main->token = ft_lstnew(command, main);
	else
		ft_lstadd_back(&main->token, ft_lstnew(command, main));
	free(command);
	return (&line[start + end]);
}
