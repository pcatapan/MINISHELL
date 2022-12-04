/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:54:17 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 17:55:56 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_or(t_token *token, t_main *main)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				;
		}
	}
	else
		ft_export(token, main);
}

void	ft_check_export(t_token *token, t_main *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_export_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_export(token, main);
		}
		else
			ft_export(token, main);
	}
	else
		ft_export(token, main);
}
