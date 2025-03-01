# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:23:56 by aalahyan          #+#    #+#              #
#    Updated: 2025/01/25 17:42:00 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC=cc
BINDIR=bin
CFLAGS=-Wall -Wextra -Werror
CFILES=		ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\
			get_next_line.c\
			ft_strjoin_gnl.c\
			ft_char_exist.c\
			pf_putchar_bonus.c\
			print_adress_bonus.c\
			print_character_bonus.c\
			print_hex_number_bonus.c\
			print_signed_number_bonus.c\
			print_string_bonus.c\
			print_unsigned_number_bonus.c\
			utils_printf_2_bonus.c\
			utils_printf_bonus.c \
			ft_printf_bonus.c

OFILES = $(CFILES:%.c=$(BINDIR)/%.o)


HEADERFILE= libft.h

NAME = libft.a 

all: $(BINDIR) $(NAME)

bonus: $(BINDIR) $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $^

$(BINDIR)/%.o: %.c $(HEADERFILE)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BINDIR):
	mkdir -p $@
clean: 
	rm -rf $(BINDIR)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re