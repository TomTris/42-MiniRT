NAME			= minirt
CFLAGS			= -Wextra -Wall -Werror
CC 				= cc

SRC_DIR = bonus
FT_LIBS =	MLX42/build/libmlx42.a

SRC	= $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)

OBJS = $(SRC:.c=.o)

all:  $(NAME)

$(NAME): $(FT_LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -lm -g

$(FT_LIBS):
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	rm -rf $(OBJS)
# rm -rf MLX42

fclean: clean
	rm -rf $(NAME)


re: fclean all
