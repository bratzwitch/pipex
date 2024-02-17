# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 14:02:36 by vmoroz            #+#    #+#              #
#    Updated: 2024/02/17 14:30:54 by vmoroz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./lib_ft

SRC =	./src/check_file_permissions.c ./src/env_path.c \
		./src/exec_command.c ./src/file_utils.c \
		./src/heredoc.c ./src/main.c \
		./src/pipex_utils.c ./src/pipex.c

OBJS = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		@make -C $(LIBFT) && make clean -C $(LIBFT)
		@cc $(CFLAGS) $(OBJS) -o $(NAME) ./lib_ft/libft.a && make clean
		@echo "All good you can rest(no)"
clean:
		$(RM) $(OBJS)

fclean:	clean
		make fclean -C $(LIBFT)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
