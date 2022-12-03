/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:57:31 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:39:37 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_divide_line(char *line, t_token *token, t_main *main)
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

char	*ft_search_harder(t_main *main, char *cmd)
{
	int		i;

	i = 0;
	while (main->paths[i])
	{
		main->part_path = ft_strjoin(main->paths[i], "/");
		main->right_path = ft_strjoin(main->part_path, cmd);
		free(main->part_path);
		if (access(main->right_path, F_OK) == 0)
		{
			ft_free_matrix(main->paths);
			return (main->right_path);
		}
		free(main->right_path);
		i++;
	}
	ft_free_matrix(main->paths);
	return (NULL);
}

char	*ft_find_path(char *cmd, t_main *main)
{
	int		i;
	int		len;

	i = 0;
	len = ft_matrixlen(main->copy_env);
	if (ft_strnstr(cmd, "/bin/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	while (main->copy_env[i])
	{
		if (!(ft_strncmp("PATH=", main->copy_env[i], 5)))
			break ;
		i++;
	}
	if (i >= len)
	{
		g_exit = 127;
		return (NULL);
	}
	main->paths = ft_split(main->copy_env[i] + 5, ":");
	return (ft_search_harder(main, cmd));
}

/*
Aggiungere funzione per settare priorita, ideale prima dello strudup
prima di passare a path bisogna pulire il paramentro da eventuali '('
come chiuderla?
*/

void	ft_trimming(t_main *main, t_token *token, int i)
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
