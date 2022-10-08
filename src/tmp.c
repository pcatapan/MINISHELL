/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:46:39 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/08 17:47:10 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_lst(t_token *token)
{
	int		i;
	t_token	*a;

	a = ft_return_head(token);
	while (a)
	{
		printf("%s --- Comand\n", a->command);
		i = -1;
		while (a->value[++i] != NULL)
			printf("%s --- Value %d\n", a->value[i], i);
		printf("%d -- Priority\n", a->priority);
		printf("%d -- Bool Res\n", a->res);
		printf("%d -- Bool And\n", a->and);
		printf("%d -- Bool Or\n", a->or);
		if (!a->next)
			break ;
		a = a->next;
	}
}
