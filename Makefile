NAME				= minirt
NAME_BONUS			= minirt_bonus
CFLAGS				= -Wextra -Wall -Werror
CC 					= cc

SRC_BONUS = \
		bonus/main.c \
		bonus/display/checkers.c \
		bonus/display/display.c \
		bonus/display/display2.c \
		bonus/display/get_ray_direction.c \
		bonus/display/handle_cones.c \
		bonus/display/handle_cylinders.c \
		bonus/display/handle_planes.c \
		bonus/display/handle_spheres.c \
		bonus/display/hooks.c \
		bonus/display/lightning.c \
		bonus/display/put_pixel.c \
		bonus/get_next_line/get_next_line.c \
		bonus/get_next_line/get_next_line_utils.c \
		bonus/math/utils.c \
		bonus/math/utils2.c \
		bonus/math/utils_matrix.c \
		bonus/math/utils_vec3.c \
		bonus/math/utils_vec3_2.c \
		bonus/math/utils_vec3_3.c \
		bonus/math/utils_vec3_4.c \
		bonus/parsing/calculate_up.c \
		bonus/parsing/errors.c \
		bonus/parsing/is_ok.c \
		bonus/parsing/is_ok1.c \
		bonus/parsing/is_ok2.c \
		bonus/parsing/line_x_cone_0.c \
		bonus/parsing/line_x_cone_0_vector_related1.c \
		bonus/parsing/line_x_cone_0_vector_related2.c \
		bonus/parsing/line_x_cone_1_bottom.c \
		bonus/parsing/line_x_cone_1_bottom_in_plain.c \
		bonus/parsing/line_x_cone_2_0_surface.c \
		bonus/parsing/line_x_cone_2_1_surface_intersection.c \
		bonus/parsing/line_x_cone_2_2_color.c \
		bonus/parsing/parse.c \
		bonus/parsing/parse_a.c \
		bonus/parsing/parse_c.c \
		bonus/parsing/parse_co.c \
		bonus/parsing/parse_cy.c \
		bonus/parsing/parse_l.c \
		bonus/parsing/parse_pl.c \
		bonus/parsing/parse_sp.c \
		bonus/texturing/cylinder_texture.c \
		bonus/texturing/cylinder_texture2.c \
		bonus/texturing/plane_texture.c \
		bonus/texturing/sphere_texture.c \
		bonus/utils/free_data.c \
		bonus/utils/ft_split.c \
		bonus/utils/str_to_double.c \
		bonus/utils/utils1.c \
		bonus/utils/utils2.c \
		bonus/utils/utils3.c


SRC = \
		src/main.c \
		src/display/display.c \
		src/display/display2.c \
		src/display/get_ray_direction.c \
		src/display/handle_cylinders.c \
		src/display/handle_planes.c \
		src/display/handle_spheres.c \
		src/display/hooks.c \
		src/display/lightning.c \
		src/display/put_pixel.c \
		src/get_next_line/get_next_line.c \
		src/get_next_line/get_next_line_utils.c \
		src/math/utils.c \
		src/math/utils2.c \
		src/math/utils_matrix.c \
		src/math/utils_vec3.c \
		src/math/utils_vec3_2.c \
		src/math/utils_vec3_3.c \
		src/math/utils_vec3_4.c \
		src/parsing/calculate_up.c \
		src/parsing/errors.c \
		src/parsing/is_ok.c \
		src/parsing/parse.c \
		src/parsing/parse_a.c \
		src/parsing/parse_c.c \
		src/parsing/parse_co.c \
		src/parsing/parse_cy.c \
		src/parsing/parse_l.c \
		src/parsing/parse_pl.c \
		src/parsing/parse_sp.c \
		src/utils/free_data.c \
		src/utils/ft_split.c \
		src/utils/str_to_double.c \
		src/utils/utils1.c \
		src/utils/utils2.c \
		src/utils/utils3.c

FT_LIBS =	MLX42/build/libmlx42.a

SRC_OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(SRC_BONUS:.c=.o)


all:  $(NAME)

$(NAME): $(FT_LIBS) $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -lm -g

$(NAME_BONUS): $(FT_LIBS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(FT_LIBS) -o $(NAME_BONUS) -ldl -lglfw -lm -g

$(FT_LIBS):
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	@rm -rf $(SRC_OBJS)
	@rm -rf $(BONUS_OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@rm -rf MLX42

re: fclean all

bonus: $(NAME_BONUS)