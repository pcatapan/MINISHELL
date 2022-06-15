/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:47:12 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/15 21:01:58 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>

void sig_handler(int signal)
{
     if (signal == SIGINT)
        printf("42minishell %%\n");
    if (rl_on_new_line() == -1)
        exit(1);
    rl_replace_line("", 1);
    rl_redisplay();  
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN); 
}

int main(void)
{
	char 			*line;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	setting_signal();
	while (1)
	{
		line = readline("42minishell %% ");
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
