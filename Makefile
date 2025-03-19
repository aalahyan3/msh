# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:06:07 by aalahyan          #+#    #+#              #
#    Updated: 2025/03/19 17:39:22 by aaitabde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = #-Wall -Wextra -Werror 
NAME = minishell

SRCS = 	minishell.c \
		ft_func/ft_fork.c\
		ft_func/ft_isspace.c\
		env/build_env.c\
		env/clear_env.c\
		free_utils/free_2d_array.c\
		expansion/expand_vars.c\
		expansion/expand.c\
		expansion/split_by_quotes.c\
		expansion/split_msh.c\
		expansion/split_not_quotes.c\
		expansion/split_and_join.c\
		expansion/expand_quotes.c\
		expansion/expand_wildcards.c\
		expansion/expand_here_doc.c\
		parser/process_prompt.c\
		parser/tokenize.c\
		parser/parsing.c\
		parser/free_ast.c\
		parser/build_ast.c\
		parser/ast_vis.c\
		parser/get_redirections.c\
		parser/expand_block.c\
		parser/free_red_structs.c\
		executor/execute_ast.c\
		executor/execute_pipe.c\
		executor/execute_simple_cmd.c\
		executor/command_path_utils.c\
		executor/get_cmd_arguments.c\
		executor/signals_handeling.c\
		executor/redirections_heredoc.c\
		executor/redirections_error_display.c\
		parser/asstes.c\
		executor/builtins_echo.c\
		executor/builtins_pwd.c\
		executor/builtins_cd.c\
		executor/builtins_env.c\
		executor/builtins_unset.c\

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

BIN = bin
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SRCS:.c=.o)))


all bonus: libft $(NAME)

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
$(BIN)/%.o: expansion/%.c
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re