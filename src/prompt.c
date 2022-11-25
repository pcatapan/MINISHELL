/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:57:38 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/25 23:54:35 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_sig_handel(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*ft_set_term(char *name_shell)
{
	struct termios	new;
	struct termios	old;
	char			*rtr;	

	if (tcgetattr(STDIN_FILENO, &old))
		perror("tcgetattr1");
	new = old;
	new.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
		perror("tcsetattr2");
	rtr = readline(name_shell);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old))
		perror("tcsetattr3");
	free(name_shell);
	return (rtr);
}

char	*ft_clear_prompt(char *prompt)
{
	char	*rtr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt[i] != '\0')
		i++;
	while (prompt[i - j] != '/')
		j++;
	j--;
	rtr = ft_substr(prompt, i - j, ft_strlen(prompt));
	free(prompt);
	return (rtr);
}

char	*ft_get_line_input(char **envp)
{
	char	*prompt;
	char	*tmp;
	char	*home;
	char	*pwd;

	home = ft_searchstrchr("HOME=", envp);
	pwd = ft_searchstrchr("PWD=", envp);
	if (ft_strcmp(home, pwd))
		prompt = ft_strjoin(pwd, HOME_SHELL);
	else
		prompt = ft_strjoin(pwd, DIVISOR_SHELL);
	free(home);
	free(pwd);
	tmp = ft_clear_prompt(prompt);
	prompt = ft_strjoin(NAME_SHELL, tmp);
	free(tmp);
	prompt = ft_set_term(prompt);
	return (prompt);
}

int	ft_prompt(char **envp, t_main *main)
{
	char			*line;

	line = ft_get_line_input(main->copy_env);
	if (!line)
	{
		printf(RED "\texit\n" COLOR_RES);
		free(line);
		ft_free_matrix(main->copy_env);
		exit(127);
	}
	else if (line[0] != '\0')
	{
		main->export_env = malloc (sizeof(char **) * 1);
		if (!main->export_env)
		{
			free(line);
			ft_free_matrix(main->copy_env);
			exit(127);
		}
		main->export_env[0] = NULL;
		main->files_pwd = (char *)malloc(sizeof(char) * 256);
		if (!main->files_pwd)
		{
			free(line);
			ft_free_matrix(main->copy_env);
			ft_free_matrix(main->export_env);
			exit(127);
		}
		getcwd(main->files_pwd, 256);
		ft_add_history(line, envp);
		ft_check_syntax(line, main);
		if (!main->error)
		{
			ft_parsing(line, main);
			ft_execute_command(main->copy_line, main);
		}
		free(main->copy_line);
		free(main->files_pwd);
		// ft_free_token(main->token);
		close(main->fd_export);
		close(main->fd_matrix);
	}
	return (0);
}
