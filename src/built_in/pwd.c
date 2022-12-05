/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:44:09 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/05 16:54:03 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_pwd_or(t_token *token)
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
		ft_pwd();
}

void	ft_check_pwd(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_pwd_or(token);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_pwd();
		}
		else
			ft_pwd();
	}
	else
		ft_pwd();
}
