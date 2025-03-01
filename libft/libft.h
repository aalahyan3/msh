/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:28:57 by aalahyan          #+#    #+#             */
/*   Updated: 2025/01/24 18:27:50 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_flags
{
	int	field_w;
	int	left_alig;
	int	right_alig;
	int	precision;
	int	zero_pad;
	int	hash;
	int	space;
	int	plus;
}	t_flags;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(char const *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*get_next_line(int fd);
int		ft_char_exist(char *str, char c);
char	*ft_strjoin_gnl(char *s1, const char *s2);
void	pf_putchar(char c, int *counter);
void	print_adress_bonus(void *ptr, t_flags *flags, int *counter);
void	print_character_bonus(char c, t_flags *flags, int *counter);
void	print_hex_number_bonus(unsigned int n, t_flags *flags, \
int *counter, char type);
void	print_signed_number_bonus(int n, t_flags *flags, int *counter);
void	print_string_bonus(char *str, t_flags *flags, int *counter);
void	print_unsigned_number_bonus(unsigned int n, \
t_flags *flags, int *counter);
void	get_pad_and_zeros_int(t_flags *flags, int *pad, int *zer, int len);
void	print_persent(t_flags *flags, int *counter);
void	print_invalid_flag(char *str, int *counter);
int		is_flag(char c);
void	reverse_string(char *str, int len);
int		is_format(char c);
void	reset_flags(t_flags *flags);
void	manage_flags(va_list args, t_flags *flags, char *format, int *counter);
void	manage_flags_2(t_flags *flags, char *format);
void	manage_format_bonus(va_list args, t_flags *flags, char *\
format, int *counter);
int		ft_printf(const char *format, ...);
#endif
