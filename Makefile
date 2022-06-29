# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 01:38:13 by aanghel           #+#    #+#              #
#    Updated: 2022/06/29 02:00:39 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./src/*.c \
		./src/utils/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

USER = pcatapan

FLAGS = -Wall -Werror -Wextra #-g #-fsanitize=address

FLAG_READLINE = -lreadline -lcurses -I /Users/$(USER)/.brew/opt/readline/include #-L /Users/$(USER)/.brew/opt/readline/lib 

all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f 42minishell_history
	
re: fclean all

.PHONY: all clean fclean re