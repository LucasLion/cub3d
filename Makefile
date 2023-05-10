# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/05/10 21:32:37 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d 
CC			= gcc
FLAGS		= -Wall -Werror -Wextra -ggdb3
LIBFT		= libft/libft.a
#MLX		= MLX42/build/libmlx42.a
MLX			= libmlx42.a
HEADERS		= -I include -L ./libft -I.libft/include #-L \
				#/Users/llion/.brew/Cellar/glfw/3.3.8/lib -pthread
				#-ldl -lglfw -lm
SRC			=	main.c			\
				extracting.c 	\
				parsing.c 		\
				parsing2.c
MAP			= maps/map.cub
OBJ			= ${addprefix obj/,${notdir ${SRC:.c=.o}}}
UNAME		:= $(shell uname)

all :  ${NAME}

obj/%.o : src/%.c
	@mkdir -p obj
	@${CC} ${FLAGS} ${HEADERS} -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT) 
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(HEADERS) -o $(NAME)	
ifeq ($(UNAME),Linux)
	@echo -e "-----> cube3d           \033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d              \033[32mCOMPILED\033[0m"
endif

$(LIBFT): libft/Makefile
	@make -sC libft

libft/Makefile: libft/src/*.c libft/include/*.h
	@touch libft/Makefile

debug : $(OBJ)
	@make -sC libft
	@gcc ${FLAGS} ${OBJ} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}
ifeq ($(UNAME),Linux)
	@echo -e  "-----> cube3d    \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d       \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif

clean :
	@make clean -sC libft
	@rm -rf $(OBJ)
ifeq ($(UNAME),Linux)
	@echo -e "-----> objects          \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> objects          \033[32mREMOVED\033[0m"
endif

fclean : clean
	@rm -rf $(NAME) *.dSYM
	@make fclean -sC libft
ifeq ($(UNAME),Linux)
	@echo -e "-----> cube3d           \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d              \033[32mREMOVED\033[0m"
endif

run:
	@./$(NAME) $(MAP)

re : fclean all

.PHONY : all clean fclean run debug re
