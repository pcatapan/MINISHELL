/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/07 13:43:30 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 1)
		ft_exit();
	if (ft_strcmp(cmd, "env") == 1)
		ft_env();
	if (ft_strcmp(cmd, "unset") == 1)
		ft_unset();
	if (ft_strcmp(cmd, "pwd") == 1)
		ft_pwd();
	if (ft_strcmp(cmd, "cd") == 1)
		ft_cd();
	if (ft_strcmp(cmd, "echo") == 1)
		ft_echo();
	if (ft_strcmp(cmd, "export") == 1)
		ft_export();
}

void	ft_exit(void)
{
	exit(1);
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
