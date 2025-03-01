CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS = minishell.c \
       parsing_prompt/parsing_prompt.c\
       parsing_prompt/verify_syntax.c

BIN = bin
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SRCS:.c=.o)))


all: libft $(NAME)

$(NAME): $(BIN) $(OBJS)
	$(CC) -lreadline -lft -Llibft $(OBJS) -o $(NAME)

$(BIN):
	mkdir -p $@

libft:
	make -C libft
$(BIN)/%.o: parsing_prompt/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(BIN)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean libft fclean re