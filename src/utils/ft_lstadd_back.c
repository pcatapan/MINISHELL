/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:47:41 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/28 21:11:03 by pcatapan         ###   ########.fr       */
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

// t_token	*ft_lstlast(t_token *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*temp;

// 	if (new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		temp = ft_lstlast(*lst);
// 		temp->next = new;
// 		new->prev = temp;
// 	}
// }
