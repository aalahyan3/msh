# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:06:07 by aalahyan          #+#    #+#              #
#    Updated: 2025/04/09 22:56:21 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g -fsanitize=address#-Wall -Wextra -Werror 
NAME = minishell

SRCS = 	minishell.c \
		read_input.c \
		env/build_env.c\
		env/clear_env.c\
		env/build_default_env.c\
		free_utils/free_2d_array.c\
		expansion/expand_vars.c\
		expansion/expand.c\
		expansion/split_by_quotes.c\
		expansion/split_msh.c\
		expansion/split_not_quotes.c\
		expansion/expand_quotes.c\
		expansion/expand_wildcards.c\
		expansion/expand_here_doc.c\
		expansion/new_expand_string.c\
		expansion/new_join_and_split.c\
		expansion/expand_string_2.c\
		expansion/wildcard_expander.c\
		expansion/expand_filename.c\
		expansion/utils.c\
		expansion/expand_quotes_str.c\
		parser/process_prompt.c\
		parser/tokenize.c\
		parser/parsing.c\
		parser/free_ast.c\
		parser/build_ast.c\
		parser/ast_vis.c\
		parser/get_redirections.c\
		parser/asstes.c\
		parser/valid_blocks.c\
		parser/expand_block.c\
		parser/initial_checks.c\
		parser/linear_parsing.c\
		parser/get_next_cmd.c\
		parser/get_next_red.c\
		parser/error_buff.c\
		executor/execute_ast.c\
		executor/execute_pipe.c\
		executor/execute_simple_cmd.c\
		executor/command_path_utils.c\
		executor/get_cmd_arguments.c\
		executor/signals_handeling.c\
		executor/redirections_heredoc.c\
		executor/increment_shlvl.c\
		executor/execute.c\
		parser/get_next_token.c\
		parser/max_heredoc_check.c\
		free_utils/free_env_list.c\
		builtins/echo.c\
		builtins/cd.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/exit.c\


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
$(BIN)/%.o: builtins/%.c
	$(CC) $(READLINE_COMPILE) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re