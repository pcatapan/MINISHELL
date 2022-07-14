/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/14 21:05:28 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_lst(t_token *a)
{
	int	i;

	printf("%s --- Comand\n", a->command);
	i = -1;
	while (a->value[++i] != NULL)
		printf("%s --- Value %d\n", a->value[i], i);
	printf("%d -- Priority\n", a->priority);
	printf("%d -- Bool Res\n", a->res);
	printf("%d -- Bool And\n", a->and);
	printf("%d -- Bool Or\n", a->or);
}

void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	char	**tmp_value;
	char	*copy_line;
	int		i;
	int		count;

	i = 0;
	count = 1;
	copy_line = ft_strdup(line);
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
	tmp_value = (char **)malloc(sizeof(char *) * (count + 1));
	i = -1;
	main->token = NULL;
	while (tmp[++i])
		tmp_value[i] = ft_find_token(tmp[i], main);
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_set_op_logic(copy_line, main->token);
	ft_set_priority(copy_line, main, 0);
}

/*
In tmp ho la cosa con cui sostituire
In var ho la parte del str da sostituire
ora bisogna ricreare la str e inserire  il tmp al posto del var
*/
int	ft_change_var_in_dollar(char *line, int i, t_main *main)
{
	char	*var;
	char	*tmp;
	int		end;
	int		start;

	end = 0;
	start = i + 1;
	while (line[++i] != 32)
		end++;
	tmp = ft_substr(line, start, end);
	var = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_searchstrchr(var, main->copy_env);
	free(var);
	return (i);
}

void	ft_expand_dollar(char *line, t_main *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			while (line[++i])
			{
				if (line[i] == '$')
					i = ft_change_var_in_dollar(line, i, main);
			}
		}
		i++;
	}
}

void	ft_check_command(char *line, t_main *main)
{
	pid_t	pid;

	ft_expand_dollar(line, main);
	ft_parsing(line, main);
	main->token = ft_return_head(main->token);
	while (main->token)
	{
		ft_print_lst(main->token);
		if (!main->token->next)
			break ;
		main->token = main->token->next;
	}
	// pid = fork();
	// if (pid == -1)
	// 	exit(0);
	// if (pid == 0)
	// {
	// 	//check_built_in(main->token->value[0]);
	// 	if (!main->token->command)
	// 		printf("ERRORE CON PATH IN PARSING --LINE 159\n");
	// 	if (execve(main->token->command, main->token->value, main->copy_env))
	// 		perror(main->token->value[0]);
	// 	exit(0);
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
