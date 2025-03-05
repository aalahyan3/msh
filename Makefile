CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS = minishell.c \
       parsing_prompt/parsing_prompt.c\
       parsing_prompt/verify_syntax.c\
       parsing_prompt/split_msh.c\
       parsing_prompt/split_into_tokens.c\
       parsing_prompt/get_token_array.c

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
$(BIN)/%.o: parsing_prompt/%.c parsing_prompt/parsing.h
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@
$(BIN)/%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re