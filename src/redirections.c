/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/14 15:17:05 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    ft_output_redirect(t_token *token)
{
    int fd;

    if (token->output == 1)
        fd = open (token->next->value[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		
    else if (token->append == 1)
        fd = open (token->next->value[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		exit(0);
	}
	
}

void	ft_input_redirect(t_token *token, t_main *main)
{
	int fd;

	if (token->input == 1)
	{
		fd = open (token->next->value[0], O_RDONLY);
		if (fd == -1)
		{
			perror(RED ERROR_FILE COLOR_RES);
			write(fd, "1", 1);
			exit(0);
		}
	}
	else if (token->heredoc == 1)
	{	
		if (ft_heredoc(token, main) == -1)
		{
			perror(RED ERROR_FILE COLOR_RES);
			write(fd, "1", 1);
			exit(0);
		}	
	}
}

void    ft_redirections(t_token *token, t_main *main)
{
	while (token)
	{
    	if (token->output == 1 || token->append == 1)
        	ft_output_redirect(token);
        if (token->input == 1 || token->heredoc == 1)
        	ft_input_redirect(token, main);
		token = token->next;
	}
}