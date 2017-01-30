##
## Makefile for  in /home/romain/Projet/Tek3/Qt/tmp
## 
## Made by Romain Maingre
## Login   <maingr_r@epitech.net>
## 
## Started on  Sat Jan  9 18:32:29 2016 Romain Maingre
## Last update Sun Jan 10 22:47:16 2016 Romain Maingre
##

CPPFLAGS	+=	-W -Wall -Wextra -Werror -ansi -pedantic -std=c++11

NAME		=	discriminator

SRC		=	main.cpp		\
			Discriminator.cpp	\
			Point.cpp		\
			Vector2.cpp 		\
			Jarvis.cpp

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++

RM		=	rm -f

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CC) -o $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all clean fclean re
