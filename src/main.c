/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/26 21:14:44 by aanghel          ###   ########.fr       */
=======
/*   Updated: 2022/11/20 07:15:02 by aanghel          ###   ########.fr       */
>>>>>>> parent of d679adb... fix primi leaks echo ciao
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
	char	*tmp;

	(void)argc;
	(void)argv;
	main = (t_main *)malloc(sizeof(t_main));
	main->token = (t_token *)malloc(sizeof(t_token));
	if (!main || !main->token)
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
	{
<<<<<<< HEAD
		tmp = getcwd(NULL, 0);
		main->files_pwd = ft_strjoin(tmp, "/");
		free(tmp);
		if (!main->copy_env)
			main->copy_env = ft_init_envp(envp);
=======
>>>>>>> parent of d679adb... fix primi leaks echo ciao
		ft_prompt(main->copy_env, main);
		free(main->files_pwd);
	}
	ft_free_main(main);
}
