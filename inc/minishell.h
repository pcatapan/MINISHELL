/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:59:21 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/23 17:55:50 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>

typedef struct s_data
{
	int		input; //da valutare sia il tipo e sia se serve veramente
	int		output; //idem di input
	s_token	*token;
}	t_data;

typedef struct s_token
{
	char	command;
	char	value;
	char	sep;
	int		priority;
	s_token	*next;
	s_token	*prev;
}	t_token;


#endif