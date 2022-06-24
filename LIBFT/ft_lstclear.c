/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:17:46 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/17 15:33:25 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*swap;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		swap = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = swap;
	}
	*lst = 0;
}
