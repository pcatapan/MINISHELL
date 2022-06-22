# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 01:38:13 by aanghel           #+#    #+#              #
#    Updated: 2022/06/23 01:45:05 by aanghel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME: minishell

SRC: #vari file.c

CC: gcc

FLAGS: -Wall -Werror -Wextra

FLAG_READLINE: -lreadline -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib

OBJC: $( SRC:%.c=%.o)

$(NAME) : $(SRC)
	$(CC) $(FLAG_READLINE) $(FLAGS) @nomefile.c -o $(NAME)
	
all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: all fclean 

.PHONY: all clean fclean re