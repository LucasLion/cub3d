# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/05/07 02:37:17 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d 
CC = gcc
#FLAGS = -Wall -Werror -Wextra -ggdb3
FLAGS = -ggdb3
LIBFT = ./libft/libft.a 
HEADERS = -I include -I libft libmlx42.a -L \
		  /Users/llion/.brew/Cellar/glfw/3.3.8/lib \
		  -ldl -lglfw -pthread -lm
SRC = 	main.c

UNAME := $(shell uname)
OBJ = ${addprefix obj/,${notdir ${SRC:.c=.o}}}

all :  ${NAME}

obj/%.o : src/%.c
	@mkdir -p obj
	@${CC} ${FLAGS} ${HEADERS} -c $< -o $@


$(NAME) : $(OBJ) 
	@ctags -R
	@make -sC libft
	@gcc  $(FLAGS) $(OBJ) $(LIBFT) $(HEADERS) -o $(NAME)	
ifeq ($(UNAME),Linux)
	@echo -e "-----> cube3d        \033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d        \033[32mCOMPILED\033[0m"
endif
	

debug : $(OBJ) $(OBJBONUS) 
	@make -sC libft
	@gcc ${FLAGS} ${OBJ} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}
ifeq ($(UNAME),Linux)
	@echo -e  "-----> cube3d \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif

clean :
	@make clean -sC libft
	@rm -f ${OBJS} objs/%.o ${OBJBONUS} 
ifeq ($(UNAME),Linux)
	@echo -e "-----> objects          \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> objects          \033[32mREMOVED\033[0m"
endif

fclean : clean
	@rm -rf ${NAME} *.dSYM
	@make fclean -sC libft
ifeq ($(UNAME),Linux)
	@echo -e "-----> cube3d        \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> cube3d        \033[32mREMOVED\033[0m"
endif

re : fclean all

.PHONY : all clean fclean re
