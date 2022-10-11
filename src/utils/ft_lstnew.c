/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:43:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/11 18:47:33 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*nlist;

	nlist = (t_token *)malloc(sizeof(t_token));
	if (!nlist)
		return (NULL);
	nlist->command = ft_strdup(content);
	nlist->priority = 0;
	nlist->or = false;
	nlist->and = false;
	nlist->input = false;
	nlist->append = false;
	nlist->output = false;
	nlist->heredoc = false;
	nlist->res = 0;
	nlist->value = NULL;
	nlist->next = NULL;
	nlist->prev = NULL;
	return (nlist);
}
