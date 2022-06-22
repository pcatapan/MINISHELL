/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:59:21 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/23 01:33:42 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>

typedef struct s_data
{
	int		input; //da valutare sia il tipo e sia se serve veramente
	int		output; //idem di input
	int		pipe;
	char	token;
	char	**matrix;
}	t_data;

#endif