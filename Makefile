SRC =	main.c\
		check.c\
		definitions/definition.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
	

OBJ =	main.o\
		check.o\
		definitions/definition.o\
		gnl/get_next_line.o\
		gnl/get_next_line_utils.o\

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = lex

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
