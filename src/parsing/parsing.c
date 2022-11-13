/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:58:00 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 05:19:10 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_info(char **tmp, t_main *main, char *copy_line, int count)
{
	char	**tmp_value;
	int		i;

	tmp_value = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp_value)
		return ;
	i = -1;
	main->token = NULL;
	while (tmp[++i])
		tmp_value[i] = ft_find_token(tmp[i], main);
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_set_op_logic(copy_line, main->token);
	ft_set_priority(copy_line, main, 0);
	ft_set_redirections(main->token);
}

void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	char	*copy_line;
	int		i;
	int		count;

	i = 0;
	count = 1;
	copy_line = ft_strdup(line);
	main->copy_line = ft_strdup(line);
	while (line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i = ft_check_double_quote(line, main, i);
		if (line[i] != 38 && line[i] != 59 && line[i] != 124)
			i++;
		else
		{
			line[i] = 127;
			if (line[i + 1] == 38 || line[i + 1] == 124)
				count++;
			i++;
		}
	}
	tmp = ft_split_original(line, 127);
	ft_set_info(tmp, main, copy_line, count);
}
