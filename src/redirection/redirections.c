/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/20 08:05:43 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_output_redirect(t_token *token, t_main *main)
{
	int	fd;

	fd = 0;
	token->dup = dup(STDOUT_FILENO);
	if (token->output == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (token->append == 1)
	{
		printf("sono qua\n");
		fd = open (token->name_file, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		exit(0);
	}
	token->stdoutput = fd;
	if (ft_search_redir(token, "<"))
		ft_change_name_file(main, token, '<');
}

void	ft_input_redirect(t_token *token)
{
	int	fd;

	token->dup = dup(STDIN_FILENO);
	fd = open (token->name_file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		exit(1);
	}
	token->stdinput = fd;
}

void	ft_delete_redirection(t_token *token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token->value[i])
		{
			if (ft_strcmp(token->value[i], "<") \
				|| ft_strcmp(token->value[i], "<<") \
				|| ft_strcmp(token->value[i], ">") \
				|| ft_strcmp(token->value[i], ">>"))
			{
				token->value[i] = NULL;
				free(token->value[i]);
			}
			i++;
		}
	}
}

void	ft_single_redir(t_token *token, t_main *main)
{
	if (token->heredoc == 1)
		ft_heredoc(token, main);
	if (token->output == 1 || token->append == 1)
		ft_output_redirect(token, main);
	if (token->input == 1)
		ft_input_redirect(token);
	ft_delete_redirection(token);
	if (token->command == NULL)
	{
		if (token->stdoutput != STDOUT_FILENO)
			dup2(token->dup, STDOUT_FILENO);
		else if (token->stdinput != STDIN_FILENO)
			dup2(token->dup, STDIN_FILENO);
	}
	printf("Dopo dup\n");
	ft_qualcosa(token, main);
}

t_token	*ft_redirections(t_token *token, t_main *main)
{
	pid_t	pidchild;

	pidchild = fork();
	if (pidchild != 0)
		waitpid(pidchild, &token->res, 0);
	else
	{
		if (ft_count_redir_value(token) >= 1)
			ft_no_space(token);
		else
		{
			ft_single_redir(token, main);
			if (token->stdoutput != STDOUT_FILENO)
				dup2(token->dup, STDOUT_FILENO);
			else if (token->stdinput != STDIN_FILENO)
				dup2(token->dup, STDIN_FILENO);
		}
	}
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
	}
	return (token);
}
