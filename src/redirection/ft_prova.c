/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prova.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:59:00 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/20 09:10:26 by pcatapan         ###   ########.fr       */
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
	line[j] = '\0';
	return (line);
}

void	ft_token_with_space(char *line, t_token *token)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)malloc(sizeof(char) * 1);
	if (!tmp)
		perror("Stronzo");
	tmp[0] = '\0';
	while (token->value[++i])
	{
		if (ft_strchr(token->value[i], '>') || ft_strchr(token->value[i], '<'))
			break ;
	}
	token->value[i] = ft_strcpy(token->value[i], line);
	token->value[i] = ft_substr(token->value[i], 0, ft_strlen(line));
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

/*DEVIIIIII FARE free tmp*/
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
	free(tmp);
	ft_token_with_space(rtr, token);
}
