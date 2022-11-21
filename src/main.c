/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/21 19:31:59 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = (t_main *)malloc(sizeof(t_main));
	main->token = (t_token *)malloc(sizeof(t_token));
	if (!main || !main->token)
		return (0);
	main->copy_env = ft_init_envp(envp);
	main->export_env = malloc (sizeof(char **) * 1);
	main->export_env[0] = NULL;
	main->files_pwd = getcwd(NULL, 0);
	main->files_pwd = ft_strjoin(main->files_pwd, "/");
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
	{
		if (!main->copy_env)
			main->copy_env = ft_init_envp(envp);
		ft_prompt(main->copy_env, main);
	}
	ft_free_all(main);
	free(main);
}
