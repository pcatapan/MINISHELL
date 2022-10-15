/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/16 01:37:38 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exceve(t_token *token, int fd[2])
{
	if (token->prev && token->prev->or)
	{
		if (!token->res)
		{
			write(fd[1], "1", 1);
			exit(0);
		}
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: coomand not found\n"COLOR_RES, token->value[0]);
			write(fd[1], "1", 1);
			exit(0);
		}
	}
	else if (token->prev && token->prev->and)
	{
		if (token->res)
		{
			write(fd[1], "1", 1);
			exit(0);
		}
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			write(fd[1], "1", 1);
			exit(0);
		}
	}
	else if (execve(token->command, token->value, token->main->copy_env))
	{
		printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
		write(fd[1], "1", 1);
		exit(0);
	}
}

t_token	*ft_execute_exeve(t_token *token)
{
	pid_t	pidchild;
	int		fd_pipe[2];
	int		fd[2];

	if (pipe(fd) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	pidchild = fork();
	if (pidchild != 0)
	{
		close(fd[1]);//Close Write
		close(fd_pipe[1]);
		waitpid(pidchild, NULL, 0);
	}
	else
	{
		close(fd[0]);//Close Read
		close(fd_pipe[0]);
		if (token->pipe)
			dup2(fd_pipe[1], STDOUT_FILENO);
		ft_exceve(token, fd);
	}
	return (ft_end_execute_(token, fd, fd_pipe));
}

void	ft_execute_command(char *line, t_main *main)
{
	pid_t	pidchild;
	int		c;
	int		lstsize;
	int		file_desc;

	c = 0;
	lstsize = ft_lstsize(main->token);
	// ft_print_lst(main->token);
	main->token = ft_return_head(main->token);
	ft_print_lst(main->token);
	pidchild = fork();
	// Qui il processo che gestisce minishell si ferma
	if (pidchild != 0)
		wait(0);
	else
	{
		// file_desc = open("test.txt", O_WRONLY | O_APPEND);
		// dup2(file_desc, STDOUT_FILENO);
		while (c < lstsize)
		{
			// if (ft_check_builtin(main->token) && !main->redirections)
			// 	main->token = ft_execute_builtin(main->token);
			// else // Qui entra se il comando bultin é errato o se non é da gestirte
			main->token = ft_execute_exeve(main->token);
			// else if (main->redirections)
			// 	main->token = ft_execute_redirection(main->token);
			// else if (ft_strchr(main->token->value, '=') && \
			// 		ft_check_envi(main->token->value))
			// 	main->token = ft_add_var_to_env(main->token);
			// // main->copy_env = ft_add_envi(main->token->value, main);
<<<<<<< HEAD
=======
			// else if (main->redirections)
			// 	main->token = ft_execute_redirection(main->token);
			// else
			// // Qui entra se il comando bultin é errato o se non é da gestirte
			// 	main->token = ft_execute_exeve(main->token);
>>>>>>> 3b443c0100100717225c5d3263a325ac0ae6683e
			c++;
		}
		exit(0);
	}
}
