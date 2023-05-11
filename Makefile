# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/05/11 17:07:15 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:= $(shell uname)
define echo
@if [ "$(UNAME)" = "Linux" ]; then \
	echo -e "\033[$(3)m[$(1)]\033[0m\t$(2)"; \
else \
	echo "\033[$(3)m[$(1)]\033[0m\t$(2)"; \
fi
endef

NAME		= cub3d 
CC			= gcc
FLAGS		= -Wall -Werror -Wextra -ggdb3
LIBFT		= libft/libft.a
MLX			= MLX42/build/libmlx42.a
HEADERS		= -Iinclude -I.libft/include -lglfw -L /Users/$$USER/.brew/Cellar/glfw/3.3.8/lib
			  # -pthread# -ldl -lglfw -lm
SRC			=	main.c			\
				extracting.c 	\
				parsing2.c		\
				parsing.c 		\
				display_map.c 		
MAP			= maps/map.cub
OBJ			= $(addprefix obj/,$(notdir $(SRC:.c=.o)))

all :  ${NAME}

obj/%.o : src/%.c
	@mkdir -p obj
	@$(CC) ${HEADERS} -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(HEADERS) -o $(NAME)	
	$(call echo,COMPILED,cub3d,32)

$(LIBFT): libft/Makefile
	@make -sC libft

libft/Makefile: libft/src/*.c libft/include/*.h
	@touch libft/Makefile

debug: $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(HEADERS) -fsanitize=address -o $(NAME)	
	$(call echo,COMPILED,cub3d,33)

clean :
	@make clean -sC libft
	@rm -rf $(OBJ)
	$(call echo,REMOVED,objects,31)

fclean : clean
	@rm -rf $(NAME) *.dSYM
	@make fclean -sC libft
	$(call echo,REMOVED,cub3d,31)

run:
	@./$(NAME) $(MAP)

re : fclean all

.PHONY : all clean fclean run debug re
