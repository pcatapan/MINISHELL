/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_space_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:38:48 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/16 00:53:49 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_new_token(t_token *token, char *line, char dir)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(2));
	tmp[0] = dir;
	tmp[1] = '\0';
	i = -1;
	while (token->value[++i])
		if (ft_strchr(token->value[i], dir))
			break ;
	free(token->value[i]);
	token->value[i] = ft_strdup(tmp);
	token->value[i + 1] = ft_strdup(line);
	token->value[i + 2] = NULL;
	if (ft_strcmp(token->value[i], ">") == 1)
			token->output = true;
	else if (ft_strcmp(token->value[i], "<") == 1)
			token->input = true;
	ft_print_lst(token);
	ft_single_redir(token, token->main);
}
