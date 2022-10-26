/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:43:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 15:31:02 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_lstnew(void *content, t_main *main)
{
	t_token	*nlist;

	nlist = (t_token *)malloc(sizeof(t_token));
	if (!nlist)
		return (NULL);
	nlist->command = ft_strdup(content);
	nlist->value = NULL;
	nlist->priority = 0;
	nlist->res = 0;
	nlist->dup = STDIN_FILENO;
	nlist->stdinput = STDIN_FILENO;
	nlist->output = STDOUT_FILENO;
	nlist->or = false;
	nlist->and = false;
	nlist->pipe = false;
	nlist->input = false;
	nlist->append = false;
	nlist->output = false;
	nlist->heredoc = false;
	nlist->name_file = NULL;
	nlist->main = main;
	nlist->prev = NULL;
	nlist->next = NULL;
	return (nlist);
}
