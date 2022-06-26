/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:47:12 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/26 03:06:52 by pcatapan         ###   ########.fr       */
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
		perror("tcgetattr");
	new = old;
	new.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
		perror("tcsetattr");
	rtr = readline(name_shell);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old))
		perror("tcsetattr");
	free(name_shell);
	return (rtr);
}

char	*ft_clear_pwd(char  *prompt)
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
	char	*home;
	char	*pwd;
	int		i;

	home = ft_searchstrchr("HOME=", envp);
	pwd = ft_searchstrchr("PWD=", envp);
	i = 0;
	while (envp[i])
	{
		if(ft_strcmp(home, pwd) == 0)
			prompt = ft_strjoin(pwd, " % ");
		else
			prompt = ft_strjoin(pwd, " % ");
		i++;
	}
	free(home);
	free(pwd);
	prompt = ft_clear_pwd(prompt);
	prompt = ft_strjoin(NAME_SHELL, prompt);
	prompt = ft_set_term(prompt);
	return (prompt);
}

int	ft_prompt_loop(char **envp)
{
	char			*line;

	signal(SIGINT, ft_sig_handel); // CTRL + C
	signal(SIGQUIT, ft_sig_handel);
	while (1)
	{
		line = ft_get_line_input(envp);
		if (!line)
		{
			printf("\nSaving session...\n"
			"...copying shared history...\n"
			"...saving history...truncating history files..."
			"\n...completed.\n\n[Processo completato]\n");
			exit(-1);
		}
		else if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	return (0);
}
