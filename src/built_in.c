/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/13 18:00:59 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_built_in(t_main *main)
{
	if (ft_strcmp(main->token->value[0], "exit") == 1)
		ft_exit();
	if (ft_strcmp(main->token->value[0], "env") == 1)
		ft_env();
	if (ft_strcmp(main->token->value[0], "unset") == 1)
		ft_unset();
	if (ft_strcmp(main->token->value[0], "pwd") == 1)
		ft_pwd();
	if (ft_strcmp(main->token->value[0], "cd") == 1)
		ft_cd();
	if (ft_strcmp(main->token->value[0], "echo") == 1)
		ft_echo();
	if (ft_strcmp(main->token->value[0], "export") == 1)
		ft_export();
}

void	ft_exit(void)
{

}

void	ft_env(void)
{
	exit(1);
}

void	ft_unset(void)
{
	exit(1);
}

void	ft_pwd(void)
{
	exit(1);
}

void	ft_cd(void)
{
	exit(1);
}

void	ft_echo(void)
{
	exit(1);
}

void	ft_export(void)
{
	exit(1);
}
