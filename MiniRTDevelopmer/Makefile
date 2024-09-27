NAME			= minirt
CFLAGS			= -Wextra -Wall -Werror -fsanitize=address -g
CC 				= cc
SRC	= 0.checker1.c 0.checker2.c 0.checker3.c \
	1.create_line.c \
	2.create_plain.c \
	3.find_point.c \
	4.check_point_inside_bottom_area.c \
	4.check_point_inside_triangle.c


OBJS = $(SRC:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g


clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
