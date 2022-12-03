/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:01:24 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 16:09:45 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_return_head(t_token *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

int	ft_support_parsing(char *line, t_main *main, int i)
{	
	i = ft_check_single_quote(line, main, i);
	i = ft_check_double_quote(line, main, i);
	i = ft_jump_brackets(line, i);
	return (i);
}
