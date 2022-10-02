/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:56:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/02 18:51:37 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
Altra ipotesi per gestire le () farle saltre sullo start e end
successivamnte andare a fare check sulla copy, come fatto con gli op_logic
!Soluzione che al momento mi sembra la migliore
*/
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
		main->token = ft_lstnew(command);
	else
		ft_lstadd_back(&main->token, ft_lstnew(command));
	//free(command);
	return (&line[start + end]);
}
