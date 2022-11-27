/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prova.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:59:00 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/27 07:55:35 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_new_line(char *tmp, int count)
{
	char	*line;
	int		i;
	int		len;
	int		j;

	len = ft_strlen(tmp);
	line = (char *)malloc(sizeof(char) * (len + count + 1));
	if (!line)
		return (0);
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
	line[j] = '\0';
	return (line);
}

void	ft_token_with_space(char *line, t_token *token)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp2 = ft_strdup(line);
	free(line);
	while (token->value[++i])
	{
		if (ft_strchr(token->value[i], '>') || ft_strchr(token->value[i], '<'))
			break ;
		else if (i == 0)
			tmp = ft_strdup(token->value[i]);
		else
		{
			tmp = ft_strjoin(tmp, token->value[i]);
		}	
	}
	tmp = ft_strjoin(tmp, tmp2);
	printf("tmp: %s\n", tmp);
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
	printf("i: %d --- value: %s\n", i, token->value[i]);
	tmp = ft_strdup(token->value[i]);
	printf("tmp: %s\n", tmp);
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
	printf("count: %d\n", count);
	rtr = ft_new_line(tmp, count * 2);
	printf("rtr: %s\n", rtr);
	free(tmp);
	ft_token_with_space(rtr, token);
}
