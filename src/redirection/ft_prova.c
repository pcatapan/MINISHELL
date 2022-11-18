/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prova.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:59:00 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/18 13:53:01 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_new_line(char *tmp, int count)
{
	char	*line;
	int		i;
	int		j;

	line = (char *)malloc(sizeof(ft_strlen(tmp) + 1 + (count * 2)));
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '<' && tmp[i + 1] == '<' && tmp[i - 1] != '<') \
				|| (tmp[i] == '>' && tmp[i + 1] == '>' && tmp[i - 1] != '>'))
		{
			line[j] = ' ';
			line[j + 1] = tmp[i];
			line[j + 2] = tmp[i + 1];
			line[j + 3] = ' ';
			j += 4;
			i += 2;
		}
		else if ((tmp[i] == '<' && tmp[i + 1] != '<' && tmp[i - 1] != '<') \
				|| (tmp[i] == '>' && tmp[i + 1] != '>' && tmp[i - 1] != '>'))
		{
			line[j] = ' ';
			line[j + 1] = tmp[i];
			line[j + 2] = ' ';
			j += 3;
			i++;
		}
		else
		{
			line[j] = tmp[i];
			j++;
			i++;
		}
	}
	return (line);
}

void	ft_token_with_space(char *line, t_token *token)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)malloc(sizeof(char) + 1);
	while (token->value[++i])
		if (ft_strchr(token->value[i], '>') || ft_strchr(token->value[i], '<'))
			break ;
	token->value[i] = ft_strcpy(token->value[i], line);
	token->value[i] = ft_substr(token->value[i], 0, ft_strlen(line));
	tmp[0] = '\0';
	i = -1;
	while (token->value[++i])
	{
		tmp = ft_strjoin(tmp, token->value[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	ft_set_new_valus(token, tmp);
	ft_set_redirections(token);
	ft_execute_multi_redir(token);

}

void	ft_no_space(t_token *token)
{
	int		i;
	char	*tmp;
	int		count;
	char	*rtr;

	i = -1;
	while (token->value[++i])
		if (ft_strchr(token->value[i], '>') || ft_strchr(token->value[i], '<'))
			break ;
	tmp = (char *)malloc(sizeof(ft_strlen(token->value[i])));
	if (!tmp)
		return ;
	tmp = ft_strdup(token->value[i]);
	i = -1;
	count = 0;
	while (tmp[++i])
	{
		if ((tmp[i] == '<' && tmp[i + 1] != '<' && tmp[i - 1] != '<') \
				|| (tmp[i] == '>' && tmp[i + 1] != '>' && tmp[i - 1] != '>') \
				|| (tmp[i] == '<' && tmp[i + 1] == '<') \
				|| (tmp[i] == '>' && tmp[i + 1] == '>'))
			count++;
	}
	rtr = ft_new_line(tmp, count);
	ft_token_with_space(rtr, token);
}
