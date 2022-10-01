/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:18:02 by pcatapan          #+#    #+#             */
/*   Updated: 2022/09/30 13:25:45 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_token *lst_or)
{
	int		c;
	t_token	*cpy;

	c = 0;
	cpy = lst_or;
	while (cpy != NULL)
	{
		c++;
		cpy = cpy->next;
	}
	return (c);
}
