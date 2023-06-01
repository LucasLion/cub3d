# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 19:07:53 by llion             #+#    #+#              #
#    Updated: 2023/05/31 18:27:21 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
UNAME		:= $(shell uname)
define echo
@if [ "$(UNAME)" = "Linux" ]; then \
	echo -e "\033[$(3)m[$(1)]\033[0m\t$(2)"; \
else \
	echo "\033[$(3)m[$(1)]\033[0m\t$(2)"; \
fi
endef

SRCS		= src/ft_isalpha.c      \
			  src/ft_isdigit.c      \
			  src/ft_isalnum.c      \
			  src/ft_isascii.c      \
			  src/ft_isprint.c      \
			  src/ft_strlen.c       \
			  src/ft_memset.c	    \
			  src/ft_bzero.c        \
			  src/ft_memcpy.c       \
			  src/ft_memmove.c      \
			  src/ft_strlcpy.c      \
			  src/ft_strlcat.c      \
			  src/ft_toupper.c      \
			  src/ft_tolower.c      \
			  src/ft_strchr.c       \
			  src/ft_strrchr.c      \
			  src/ft_strncmp.c      \
			  src/ft_memchr.c       \
			  src/ft_memcmp.c       \
			  src/ft_strnstr.c      \
			  src/ft_atoi.c         \
			  src/ft_calloc.c       \
			  src/ft_strdup.c       \
			  src/ft_substr.c       \
			  src/ft_strjoin.c      \
			  src/ft_strtrim.c      \
			  src/ft_split.c        \
			  src/ft_itoa.c         \
			  src/ft_strmapi.c      \
			  src/ft_striteri.c     \
			  src/ft_putchar_fd.c   \
			  src/ft_putstr_fd.c    \
			  src/ft_putendl_fd.c   \
			  src/ft_putnbr_fd.c	\
			  src/ft_printf.c		\
			  src/ft_printnbr.c		\
			  src/ft_printchar.c	\
			  src/ft_printstr.c		\
			  src/ft_printuint.c	\
			  src/ft_printx_min.c	\
			  src/ft_printx.c		\
			  src/ft_printp.c		\
			  src/ft_printpct.c		\
			  src/ft_lstnew.c       \
			  src/ft_lstadd_front.c \
			  src/ft_lstsize.c      \
			  src/ft_lstlast.c      \
			  src/ft_lstadd_back.c  \
			  src/ft_lstdelone.c    \
			  src/ft_lstclear.c     \
			  src/ft_lstiter.c      \
			  src/ft_lstmap.c		\
			  src/ft_printchar.c	\
			  src/ft_printstr.c		\
			  src/ft_printuint.c	\
			  src/ft_printx_min.c	\
			  src/ft_printx.c		\
			  src/ft_printp.c		\
			  src/ft_printpct.c		\
			  src/ft_printf.c		\
			  src/ft_putchar_fd.c	\
			  src/ft_putendl_fd.c	\
			  src/ft_putstr_fd.c	\
			  src/ft_putnbr_fd.c	\
			  src/ft_numlen.c		\
			  src/ft_freetab.c		\
			  src/ft_tablen.c		\
			  src/get_next_line.c	\
			  src/get_next_line_utils.c

NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
OBJS 		= ${addprefix objs/,${notdir ${SRCS:.c=.o}}}
AR			= ar rc
RM			= rm -f
LIB			= ranlib

all:  $(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS) 
			@$(LIB) $(NAME)
			$(call echo,COMPILED,libft,34)

objs/%.o : 	src/%.c
			@mkdir -p objs
			@${CC} ${FLAGS} -I include -c $< -o $@
	
clean:		
			@$(RM) $(OBJS) objs/%.o
			$(call echo,REMOVED,libft objects,31)

fclean:		clean
			@$(RM) $(NAME)
			$(call echo,REMOVED,libft,31)

re:			fclean all

.PHONY:		all clean fclean 
