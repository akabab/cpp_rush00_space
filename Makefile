# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#              #
#    Updated: 2015/01/11 20:39:15 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	g++ -O2 $(FLAGS)
FLAGS			=	-Wall -Wextra -Werror
NAME			=	ft_retro
INCLUDES		=	./inc
SRCS			=	src/main.cpp						\
					src/Game.class.cpp					\
					src/Screen.class.cpp				\
					src/Block.class.cpp					\
					src/GameEntity.class.cpp			\
					src/Character.class.cpp				\
					src/Player.class.cpp				\
					src/Enemy.class.cpp					\
					src/Bullet.class.cpp				\
					src/Ui.class.cpp
OBJS			=	$(SRCS:src/%.cpp=obj/%.obj)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ -lncurses
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

obj:
	@mkdir -p obj

obj/%.obj: src/%.cpp
	@$(CC) -c -o $@ $< -I $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@rm -rf obj
	@echo "Cleaning" [ $(NAME) ] $(OK)

fclean: clean
	@rm -f $(NAME)
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: all clean fclean re
