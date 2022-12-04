/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:57:31 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 04:46:34 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_divide_line(char *line, t_token *token, t_main *main)
{
	int		i;
	char	**tmp;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == 32 || line[i] == ')')
			line[i] = 127;
	}
	tmp = ft_split_original(line, 127);
	i = 0;
	while (tmp[i])
	{
		token->value[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	token->value[i + 1] = NULL;
	ft_free_matrix(tmp);
}

static void	ft_trimming(t_main *main, t_token *token, int i)
{
	char	*tmp;

	token->value[i] = ft_strdup(token->command);
	free(token->command);
	token->command = ft_find_path(token->value[i], main);
	tmp = ft_strtrim2(token->value[i], '"');
	free(token->value[i]);
	token->value[i] = ft_strtrim2(tmp, '\'');
	free(tmp);
}

void	ft_set_values(char **line, t_main *main)
{
	int		j;
	int		i;
	t_token	*token;

	token = ft_return_head(main->token);
	j = 0;
	i = 0;
	while (token)
	{
		token->value = (char **)malloc(sizeof(char *) * \
							(ft_count_array(line[j], main) + 2));
		if (!token->value)
			return ;
		ft_trimming(main, token, i);
		ft_divide_line(line[j], token, main);
		if (token->next)
			token = token->next;
		else
			break ;
		j++;
	}
}
