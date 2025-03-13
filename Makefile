# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:06:07 by aalahyan          #+#    #+#              #
#    Updated: 2025/03/12 21:41:47 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -fsanitize=address -g#-Wall -Wextra -Werror 
NAME = minishell

SRCS = 	minishell.c \
		ft_func/ft_fork.c\
		env/build_env.c\
		free_utils/free_2d_array.c\
		parser/process_prompt.c\
		parser/tokenizer.c\
		parser/ast.c\
		parser/ast_visualizer.c\
		parser/ast_v.c\
		parser/expand_leafs.c\
		parser/expand_vars.c\
		parser/quotes_expansion.c\
		parser/token_generator.c\
		executor/execute_ast.c\
		executor/execute_pipe.c\
		executor/execute_simple_cmd.c\
		executor/command_path_utils.c\
		executor/get_cmd_arguments.c\
		executor/builtins_echo.c\
		executor/builtins_pwd.c\
		executor/builtins_cd.c\

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

BIN = bin
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SRCS:.c=.o)))


all: libft $(NAME)

$(NAME): $(BIN) $(OBJS)
	$(CC) $(CFLAGS) -lft -Llibft $(OBJS) $(READLINE_LINK) -o $(NAME)

$(BIN):
	mkdir -p $@

libft:
	make -C libft
$(BIN)/%.o: ft_func/%.c ft_func/ft_func.h
	$(CC) $(READLINE_COMPILE) $(CFLAGS)  -c $< -o $@
$(BIN)/%.o: %.c minishell.h
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: parser/%.c parser/parser.h
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: executor/%.c
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: env/%.c
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: free_utils/%.c
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re