/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/24 18:57:45 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	int	i;

	i = 0;
	(void)argc;
	(void)argv;
	ft_init_envp(&main.copy_env, envp);
	
}
