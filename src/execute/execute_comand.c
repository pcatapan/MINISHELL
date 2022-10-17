/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/17 21:33:55 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_qualcossa(t_token *token)
{
	// if (ft_check_builtin(main->token) && !main->redirections)
	// 	main->token = ft_execute_builtin(main->token);
	// else // Qui entra se il comando bultin é errato o se non é da gestirte
	token = ft_execute_exeve(token);
	// else if (main->redirections)
	// 	main->token = ft_execute_redirection(main->token);
	// else if (ft_strchr(main->token->value, '=') && \
	// 		ft_check_envi(main->token->value))
	// 	main->token = ft_add_var_to_env(main->token);
	// // main->copy_env = ft_add_envi(main->token->value, main);
}

void	ft_exceve(t_token *token)
{
	if (token->prev)
	{
		if (token->priority == (token->prev->priority - 1))
		{
			printf("QUALCOSA\n");
			ft_qualcossa(token);
		}
		else if (token->priority == (token->prev->priority - 2))
			exit(0);
		if (token->prev->or)
		{
			if (!token->res)
				exit(1);
			if (execve(token->command, token->value, token->main->copy_env))
			{
				printf(RED"%s: coomand not found\n"COLOR_RES, token->value[0]);
				exit(1);
			}
		}
		else if (token->prev->and)
		{
			if (token->res)
				exit(1);
			if (execve(token->command, token->value, token->main->copy_env))
			{
				printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
				exit(1);
			}
		}
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			exit(1);
		}
	}
	else
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			exit(1);
		}
	}
	exit(0);
}

t_token	*ft_execute_exeve(t_token *token)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd_pipe[1]);
		waitpid(pidchild, &token->res, 0);
	}
	else
	{
		close(fd_pipe[0]);
		if (token->pipe)
		{
			dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[1]);
		}
		ft_exceve(token);
	}
	token = ft_end_execute_(token, fd_pipe);
	return (token);
}

void	ft_execute_command(char *line, t_main *main)
{
	pid_t	pidchild;
	int		c;
	int		lstsize;

	c = 0;
	lstsize = ft_lstsize(main->token);
	main->token = ft_return_head(main->token);
	// ft_print_lst(main->token);
	while (c < lstsize)
	{
		// ft_execute_dollar(main->token);
		// if (ft_check_builtin(main->token) && !main->redirections)
		// 	main->token = ft_execute_builtin(main->token);
		/*else*/ if (ft_strchr(main->token->value[0], '=') && ft_check_envi(main->token->value[0]))
			main->token = ft_execute_enviroment(main->token, main->token->value[0]);
		// else // Qui entra se il comando bultin é errato o se non é da gestirte
			main->token = ft_execute_exeve(main->token);
		// else if (main->redirections)
		// 	main->token = ft_execute_redirection(main->token);
		// // main->copy_env = ft_add_envi(main->token->value, main);
		c++;
	}
	if (main->token->stdinput != STDIN_FILENO)
	{
		printf("ERRORE 3\n");
		dup2(STDIN_FILENO, STDIN_FILENO);
		printf("ERRORE 4\n");
	}
}
// 	if (read(file_desc[0], NULL, 1))
// 	{
// 		ft_free_matrix(main->set_variables);
// 		main->set_variables = ft_get_next_line(file_desc[0]);
// 	}
// }
