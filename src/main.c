/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/28 23:24:41 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = (t_main *)malloc(sizeof(t_main));
	if (!main)
		return (0);
	main->copy_env = ft_init_envp(envp);
	main->export_env = malloc (sizeof(char **) * 1);
	if (!main->export_env)
	{
		ft_free_matrix(main->copy_env);
		return (0);
	}
	main->export_env[0] = NULL;
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_prompt(main->copy_env, main);
	ft_free_matrix(main->copy_env);
	// free(main);
}
