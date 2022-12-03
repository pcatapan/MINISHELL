#include "../../inc/minishell.h"

static bool	ft_support(char *line, int i, bool error)
{
	if (line[++i] == '{')
	{
		while (line[++i] != 32 && line[i])
		{
			if (line[i] == '}')
			{
				error = FALSE;
				break ;
			}
		}
	}
	else
		error = FALSE;
	return (error);
}

bool	ft_expand_check(char *line)
{
	int		i;
	bool	error;

	i = 0;
	error = TRUE;
	while (line[i] != '$')
		i++;
	error = ft_support(line, i, error);
	if (error)
	{
		ft_putendl_fd(RED ERROR_CLOSE_ COLOR_RES, STDOUT_FILENO);
		return (TRUE);
	}
	return (FALSE);
}
