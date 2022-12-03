/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:57:38 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 18:56:23 by pcatapan         ###   ########.fr       */
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

char	*ft_get_line_input(char **copy_envp)
{
	char	*prompt;
	char	*tmp;
	char	*home;
	char	*pwd;

	home = getenv("HOME");
	pwd = getcwd(NULL, 0);
	if (ft_strcmp(home, pwd))
		prompt = ft_strjoin(pwd, HOME_SHELL);
	else
		prompt = ft_strjoin(pwd, DIVISOR_SHELL);
	free(pwd);
	tmp = ft_clear_prompt(prompt);
	prompt = ft_strjoin(NAME_SHELL, tmp);
	free(tmp);
	prompt = ft_set_term(prompt);
	return (prompt);
}

int	ft_prompt(char **envp, t_main *main)
{
	char	*line;

	line = ft_get_line_input(envp);
	if (!line)
	{
		printf(RED "\texit\n" COLOR_RES);
		g_exit = 127;
		free(main->files_pwd);
		free(main->token);
		exit(127);
	}
	else if (line[0] != '\0')
	{
		ft_add_history(line, envp);
		ft_check_syntax(line, main);
		if (!main->error)
		{
			ft_parsing(line, main);
			ft_execute_command(line, main);
			free(main->copy_line);
		}
		ft_free_token(main->token);
	}
	free(line);
	return (0);
}
