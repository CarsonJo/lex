SRC =	main.c\
		check.c\
		gnl/get_next_line_bonus.c\
		gnl/get_next_line_utils_bonus.c\
	

OBJ =	main.o\
		check.o\
		gnl/get_next_line_bonus.o\
		gnl/get_next_line_utils_bonus.o\

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = server

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re
