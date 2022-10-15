/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:43:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/15 19:26:38 by pcatapan         ###   ########.fr       */
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
	nlist->res = 0;
	nlist->priority = 0;
	nlist->main = main;
	nlist->or = false;
	nlist->and = false;
	nlist->pipe = false;
	nlist->input = false;
	nlist->append = false;
	nlist->output = false;
	nlist->heredoc = false;
	nlist->value = NULL;
	nlist->next = NULL;
	nlist->prev = NULL;
	return (nlist);
}
