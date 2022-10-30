/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:18:02 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 15:44:09 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_token *lst_or)
{
	int		c;
	t_token	*cpy;

	c = 0;
	cpy = ft_return_head(lst_or);
	while (cpy)
	{
		c++;
		cpy = cpy->next;
	}
	return (c);
}

int	ft_lstsize_this(t_token *lst_or)
{
	int		c;
	t_token	*cpy;

	c = 0;
	cpy = lst_or;
	while (cpy)
	{
		if (cpy->next && cpy->priority == cpy->next->priority)
			c++;
		cpy = cpy->next;
	}
	return (c);
}
