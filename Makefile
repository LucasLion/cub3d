# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/07/16 11:24:05 by llion@student    ###   ########.fr        #
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

NAME		= cub3D 
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra -g3
LIBFT		= libft/libft.a
MLX			= libmlx42.a
HEADERS		= -Iinclude -Ilibft/include -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw  \
			   -ldl -lglfw -lm
SRC			=	main.c				\
				extracting.c 		\
				extracting2.c 		\
				parsing2.c			\
				parsing.c 			\
				player.c 			\
				display_map.c 		\
				display_3d.c 		\
				display_3d2.c 		\
				movement.c			\
				movement2.c			\
				movement3.c			\
				find_pixel.c 		\
				rays_check.c		\
				rays_check2.c		\
				utils.c				\
				animations.c		\
				rays.c				\
				rays2.c
					
MAP			= maps/map.cub
OBJ			= $(addprefix obj/,$(notdir $(SRC:.c=.o)))

all:  $(NAME)

obj/%.o : src/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(FLAGS) $(OBJ) -Llibft -lft $(HEADERS) $(MLX) -o $(NAME)	
	$(call echo,COMPILED,cub3d,32)

$(LIBFT): libft/Makefile
	@$(MAKE) -C libft

libft/Makefile: libft/src/*.c libft/include/*.h
	@$(MAKE) -sC libft

debug: $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(HEADERS) -fsanitize=address -o $(NAME)	
	$(call echo,COMPILED,cub3d,33)

clean :
	@make clean -C libft
	@$(RM) $(OBJ)
	$(call echo,REMOVED,objects,31)

fclean : clean
	@$(RM) $(NAME) *.dSYM
	@make fclean -sC libft
	$(call echo,REMOVED,cub3d,31)

run:
	@./$(NAME) $(MAP)

re : fclean all

.PHONY : all clean fclean r libft/Makefile debug re
