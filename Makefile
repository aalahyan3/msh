# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:06:07 by aalahyan          #+#    #+#              #
#    Updated: 2025/03/07 01:06:49 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = #-Wall -Wextra -Werror
NAME = minishell

SRCS = 	minishell.c \
		ft_func/ft_fork.c\
		parser/process_prompt.c\
		parser/tokenizer.c\
		parser/ast.c\
		parser/ast_visualizer.c\
		parser/token_generator.c

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

BIN = bin
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SRCS:.c=.o)))


all: libft $(NAME)

$(NAME): $(BIN) $(OBJS)
	$(CC) -lft -Llibft $(OBJS) $(READLINE_LINK) -o $(NAME)

$(BIN):
	mkdir -p $@

libft:
	make -C libft
$(BIN)/%.o: ft_func/%.c ft_func/ft_func.h
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@
$(BIN)/%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@
$(BIN)/%.o: parser/%.c parser/parser.h
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re