/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/03 15:42:19 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_output_redirect(t_token *token, t_main *main)
{
    int fd;

    token->dup = dup(STDOUT_FILENO);
    if (token->output == 1)
    {
        fd = open (token->name_file, O_CREAT | O_RDWR, 0644);
        dup2(fd, STDOUT_FILENO);
    }
    else if (token->append == 1)
    {
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
}

void    ft_input_redirect(t_token *token, t_main *main)
{
    int fd;

    token->dup = dup(STDIN_FILENO);
    if (token->input == 1)
    {
        fd = open (token->name_file, O_RDONLY);
        dup2(fd, STDIN_FILENO);
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
    token->stdinput = fd;
}

int ft_count_redirection(t_token *token)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (token->value[i])
    {
        if (ft_strcmp(token->value[i], "<")  \
            || ft_strcmp(token->value[i], "<<") \
            || ft_strcmp(token->value[i], ">") \
            || ft_strcmp(token->value[i], ">>"))
            count++;
        i++;
    }
    return (count);
}

char    *ft_create_line(t_token *token)
{
    char    *tmp;
    char    *val;
    int     i;

    if (!(tmp = (char *)malloc(sizeof(char) * 1)))
        return (NULL);
    tmp = "\0";
    while (token->value[i])
    {
        val = ft_strjoin(token->value[i], " ");
        tmp = ft_strjoin(tmp, val);
        free(val);
        i++;
    }
    return (tmp);
}

char    *ft_set_to_del(char *line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
            line[i] = 127;
        i++;
    }
    return (line);
}

void    ft_execute_multi_redir(t_main *main)
{
    char    *line;
    char    **matrix;
    t_token *tmp_token;
	int		i;

	line = ft_set_to_del(main->copy_line);
    matrix = ft_split_original(line, 127);
    ft_set_info(matrix, main, main->copy_line, 1);
    ft_print_lst(main->token);
}

t_token *ft_redirections(t_token *token, t_main *main)
{
    pid_t   pidchild;
    char    *line;
    
    if (ft_count_redirection(token) != 1)
    {
        ft_execute_multi_redir(main);
    }
    else
    {
        pidchild = fork();
        if (pidchild != 0)
            waitpid(pidchild, 0, 0);
        else
        {
            if (token->output == 1 || token->append == 1)
                ft_output_redirect(token, main);
            if (token->input == 1 || token->heredoc == 1)
                ft_input_redirect(token, main);
            ft_delete_redirection(token);
            ft_qualcosa(token);
        }
        if (token->stdoutput != STDOUT_FILENO)
            dup2(token->dup, STDOUT_FILENO);
        else if (token->stdinput != STDIN_FILENO)
            dup2(token->dup, STDIN_FILENO);
        }
    if (token->next)
        token = token->next;
    return (token);
}

void    ft_delete_redirection(t_token *token)
{
    int i;

    i = 0;
    while (token)
    {
        if (token->output || token->input || token->append || token->heredoc)
        {
            while (token->value[i])
            {
                if (ft_strcmp(token->value[i], "<")  \
                    || ft_strcmp(token->value[i], "<<") \
                    || ft_strcmp(token->value[i], ">") \
                    || ft_strcmp(token->value[i], ">>"))
                {
                    free(token->value[i]);
                    token->value[i] = NULL;
                }
                i++;
            }
        }
        if (!token->next)
            break ;
        token = token->next;
    }
}
