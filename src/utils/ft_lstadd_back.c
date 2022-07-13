/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:47:41 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/10 19:46:07 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}

static t_token	*ft_lstlast(t_token *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
Create a funcion that copy a node and set this node withe 
the next e the prev the old node
*/
void	ft_lstcopy(t_token **lst, t_token *new)
{
	;
}
