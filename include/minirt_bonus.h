/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 22:47:59 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
// #include <gperftools/profiler.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
// # include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <sys/time.h>
# include <pthread.h>
# define TOLARANCE 0.03
# define HEIGHT 1024
# define WIDTH 1024
# define AMOUNT_OF_THREADS 6
# define BUFFER_SIZE 1024

typedef struct s_matrix3
{
	double	m[3][3];
}	t_matrix3;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_camera
{
	double	cords[3];
	double	vector[3];
	t_vec3	vec3;
	double	fov;
	t_vec3	world_up;
	t_vec3	vec3_cords;
}	t_camera;

typedef struct s_ambitient_light
{
	int		colors[3];
	double	ratio;
	t_vec3	vec3_color;
}	t_ambitient_light;

typedef struct s_light
{
	int		colors[3];
	double	ratio;
	double	cords[3];

	t_vec3	vec3_color;
	t_vec3	vec3_cords;
}	t_light;

typedef struct s_sphere
{
	int				colors[3];
	double			diameter;
	double			cords[3];

	mlx_texture_t	*texture;
	t_vec3			vec3_cords;
	t_vec3			vec3_color;
	int				checkers;
}	t_sphere;

typedef struct s_plane
{
	double			cords[3];
	double			vector[3];
	int				colors[3];

	mlx_texture_t	*texture;
	t_vec3			vec3_cords;
	t_vec3			vec3_color;
	t_vec3			vec3_norm;
	double			dist;
	int				checkers;
}	t_plane;

//ax + by + cz + d = 0
typedef struct s_plain
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_plain;

typedef struct s_cylinder
{
	int				colors[3];
	double			diameter;
	double			cords[3];
	double			vector[3];
	double			height;
	int				checkers;

	mlx_texture_t	*texture;
	t_vec3			vec3_cords;
	t_vec3			vec3_norm;
	t_vec3			vec3_color;

	t_vec3			pa;
	t_vec3			pb;
	t_plain			pl_top;
	t_vec3			bottom_ori_vec;
	t_vec3			bottom_ori_vec2;
	t_vec3			vab;
	double			r;
}	t_cylinder;

typedef struct s_cone
{
	int				colors[3];
	double			diameter;
	double			cords[3];
	double			vector[3];
	double			height;

	t_vec3			vec3_cords;
	t_vec3			vec3_norm;
	t_vec3			vec3_color;
	int				checkers;
	mlx_texture_t	*texture;

	t_vec3			vao;
	t_vec3			pa;
	t_vec3			po;
	double			r;
	t_plain			pl;
	double			value1;
	double			s;
	double			cos_al;
	double			bottom_width;
	t_vec3			bottom_ori_vec;
	t_vec3			bottom_ori_vec2;
	double			bottom_angle;
	double			bottom_angle_2;
	double			surface_width;
}	t_cone;

typedef struct s_point_x_nor_vec
{
	int		amount;
	double	t;
	t_vec3	v;
	t_vec3	p;
	t_vec3	color;
}	t_point_nvec;

typedef struct s_points
{
	int		amount;
	t_vec3	p1;
	t_vec3	p2;
	double	t1;
	double	t2;
}	t_points;

typedef struct s_line
{
	t_vec3	p;
	t_vec3	dv;
}	t_line;

typedef struct s_cal_helper
{
	double	cos_alpha;
	double	d_v;
	t_vec3	co;
	double	co_v;
	double	d_co;
	double	a;
	double	b;
	double	c;
}	t_cal_helper;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	int					displayed;

	t_camera			camera;
	t_ambitient_light	ambitient_light;
	t_light				*light;

	int					seen_camera;
	int					seen_ambitient_light;
	int					seen_light;

	t_sphere			*spheres;
	t_cylinder			*cylinders;
	t_plane				*planes;
	t_cone				*cones;

	int					amount_of_lights;
	int					amount_of_spheres;
	int					amount_of_cylinders;
	int					amount_of_planes;
	int					amount_of_cones;

	int					current;
	pthread_t			threads[AMOUNT_OF_THREADS];
	mlx_texture_t		*texture;
	t_vec3				*pixels;

	int					fd;
}	t_data;

typedef struct s_input
{
	int		*ind;
	t_data	*data;
}	t_input;

typedef struct s_ray
{
	t_vec3				ray_origin;
	t_vec3				ray_direction;
}	t_ray;

typedef struct s_var_sphere
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	descriminent;
	double	closest;
	double	t;

	t_vec3	origin;

}	t_var_sphere;

typedef struct s_hit
{
	double			hit_distance;
	t_vec3			world_position;
	t_vec3			world_normal;
	t_vec3			color;
	t_vec3			cords;
	t_vec3			normal;
	double			closest;
	int				found;
	int				type;
	t_var_sphere	vars_sp;
	t_plane			*plane;
	t_sphere		*sphere;
	t_cone			*cone;
	t_cylinder		*cylinder;
	int				checkers;
	int				type_cy;
	mlx_texture_t	*texture;
}	t_hit;

typedef struct s_abc
{
	double	a;
	double	b;
	double	c;
}	t_abc;

void				mem_set_0(void *a, size_t len);
/***************************************************************************/
/******************************* get_next_line *****************************/
/***************************************************************************/
//get_next_line
char				*get_next_line(int fd, int *finished);
char				*solve_get_next(char *str, char *buffer, int fd,
						int *finished);
char				*allocate(char *str);
char				*strjoins(char *first, char *second, char *str);
size_t				get_ind_of_n_len(char *str, int l);
char				*help_delete_25_lines(char *str, char *out, char *second,
						size_t len1);

/*********************************************************************/
/******************************* display *****************************/
/*********************************************************************/
//display/checkers.c
t_vec3				checker_plane(t_hit *hit);
t_vec3				checker_sphere(t_hit *hit);
t_vec3				stripe_at_object(t_hit *hit);
t_vec3				manage_textures(t_hit *hit);
t_vec3				get_color(t_hit *hit);

//display/display.c
int					transform_to_channel(double v);
uint32_t			get_color_from_vec3(t_vec3 vec);
void				closest_hit2(t_data *data, t_ray *ray, t_hit *hit);
void				closest_hit(t_data *data, t_ray *ray, t_hit *hit);
void				ray_trace(t_data *data, t_ray *ray, t_hit *hit);

//display/display2.c
void				set_type_distance_cy2(t_hit *hit, double dist, int var);
t_vec3				per_pixel(t_data *data, t_ray *ray, uint32_t x,
						uint32_t y);
void				*displaying(void *input);
void				display(t_data *data);

//display/get_ray_direction.c
t_vec3				get_direction_ray(t_data *data, double offset_x,
						double offset_y);

//display/handle_cones.c
void				handle_cones(t_data *data, t_ray *ray, t_hit *hit);
void				setter_cones(t_data *data, t_hit *hit, int i,
						t_point_nvec *res);

//display/handle_cylinders.c
void				set_type_distance_cy(t_hit *hit, t_data *data, int i);
void				top_circle(t_data *data, t_ray *ray, t_hit *hit, int i);
void				bottom_circle(t_data *data, t_ray *ray, t_hit *hit, int i);
void				intersection_height(t_data *data, t_ray *ray, t_hit *hit,
						int i);
void				handle_cylinders(t_data *data, t_ray *ray, t_hit *hit);

//display/handle_planes.c
void				set_type_distance_pl(t_hit *hit, t_data *data, int i);
double				get_factor(t_vec3 *norm, t_vec3	*point, t_vec3 *camera);
void				handle_planes(t_data *data, t_ray *ray, t_hit *hit);

//display/handle_spheres.c
//static void	s	etter(t_hit *hit, t_data *data, int i);
void				handle_spheres(t_data *data, t_ray *ray, t_hit *hit);

//display/hooks.c
long long			current_time_in_ms(void);
void				ft_hook_keys(void *param);
int					create_the_threads(t_data *data);
void				change_image_size_hook(void *param);

//display/lightning.c
t_vec3				random_vector(void);
int					is_in_shadow(t_data *data, t_hit *hit, t_vec3 *light_dir,
						double dist);

//void	loop_calculate_light(t_data *data, t_ray *ray, t_hit *hit,
//						t_calculate_light *cl);

//display/t_calculate_light *cl)
t_vec3				calculate_light(t_data *data, t_ray *ray, t_hit *hit);

//display/put_pixel.c 
uint32_t			get_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/******************************************************************/
/******************************* math *****************************/
/******************************************************************/
//math/utils_matrix.c
t_matrix3			create_matrix(t_vec3 axis, double angle);
t_vec3				apply_matrix(t_vec3 vec, t_matrix3 *matrix);

//math/utils_vec3_2.c
t_vec3				create_vec3(double x, double y, double z);
double				angle_between_vec(t_vec3 vec1, t_vec3 vec2);
int					are_vectors_similar(t_vec3 vec1, t_vec3 vec2);
t_vec3				create_vec3_arr(double *vec);
t_vec3				subtract(t_vec3 vec1, t_vec3 vec2);

//math/utils_vec3_3.c
t_vec3				create_vec3_color_arr(int *arr);
t_vec3				multiply_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3				shrink_vec3(t_vec3 vec, double min, double max);

//math/utils_vec3_4.c
t_vec3				vec_reflect(t_vec3 vector, t_vec3 reflected_around);
t_vec3				vec_reflect_norm(t_vec3 vector, t_vec3 reflected_around);

//math/utils_vec3.c
double				dot_product(t_vec3 vec1, t_vec3 vec2);
t_vec3				normalize(t_vec3 vec);
t_vec3				scale(t_vec3 vec, double scale);
t_vec3				add(t_vec3 vec1, t_vec3 vec2);
t_vec3				cross(t_vec3 vec1, t_vec3 vec2);

//math/utils.c
double				dot_product_d(double *vec1, double *vec2);
double				get_len_vector_d(double *vector);
void				normilize_vector_d(double *vec);
double				max_double(double v1, double v2);
double				min_double(double v1, double v2);

//math/utils2.c
double				square(double number);		

/******************************************************************/
/**************************** parsing *****************************/
/******************************************************************/
//parsing/calculate_up.c
//void	calculate_up2(t_5vars vars, t_data *data);
void				calculate_up(t_data *data);

//parsing/errors.c
void				error_message_parse_cy(int update);
void				error_message_parse_co(int update);
int					open_texture(mlx_texture_t **texture, char **path);
void				set_null(mlx_texture_t **texture, int *checkers);

//parsing/is_ok.c
int					check_is_vector_ok(double *vector);
int					check_spheres(t_data *data);
int					check_cones(t_data *data, int i);
int					check_all_vectors(t_data *data, int i);
int					check_if_ok(t_data *data);

//parsing/is_ok1.c
double				get_distance(t_vec3 *norm, t_vec3 *point, t_vec3 *camera);
int					check_planes(t_data *data, int i);

//parsing/is_ok2.c
void				cone_and_bottom(t_cone *cone);
t_plain				plain_of_bottom_area(t_cone *cone);
void				cone_and_bottom2(t_cone *cone);
void				cone_and_surface(t_cone *cone);
void				calculate_cone(t_cone *cone);

//parsing/line_x_cone_0_vector_related1.c
t_vec3				find_point_in_bottom(t_vec3 *p, t_plain *pl, t_vec3 *a);
double				alpha_2_vector(t_vec3 *v1, t_vec3 *v2);
double				cos_alpha_2_vector(t_vec3 *v1, t_vec3 *v2);
double				vector_length(t_vec3 v);
double				value_a_vector(t_vec3 vec);

//parsing/line_x_cone_0_vector_related2.c
double				dot_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3				vector_p1_to_p2(t_vec3 point1, t_vec3 point2);
double				cal_distance(t_vec3 p1, t_vec3 p2);
double				degree_2_vector(t_vec3 *v1, t_vec3 *v2);
t_vec3				vector_cross_product(t_vec3 v1, t_vec3 v2);

//parsing/line_x_cone_0.c
t_point_nvec		cone_texture_bottom(t_point_nvec *ret, t_cone *cone);
void				cone_checker_bottom(t_point_nvec *ret, t_cone *cone);
t_point_nvec		line_x_cone(t_line *line, t_cone *cone);

//parsing/line_x_cone_1_bottom_in_plain.c 
t_abc				cal_abc(t_line *li, t_cone *cone);
void				line_parallel_in_plain2(t_point_nvec *ret,
						t_line *li, t_cone *cone);
t_point_nvec		line_parallel_in_plain(t_plain *pl, t_line *li,
						t_cone *cone);

//parsing/line_x_cone_1_bottom.c
int					is_point_in_circle(t_cone *cone, t_vec3 *p);
int					is_same_side(t_plain *pl, t_vec3 p1, double value1);
t_point_nvec		line_x_cone_bottom(t_line *li, t_cone *cone);

//parsing/line_x_cone_2_0_surface.c
t_point_nvec		line_x_cone_surface1(t_cone *cone,
						t_points *points, double s);
void				line_x_cone_surface2_2(t_vec3 *cp, t_cone *cone,
						t_points *points, double s);
t_point_nvec		line_x_cone_surface2(t_line *line,
						t_cone *cone, t_points *points, double s);
t_point_nvec		line_x_cone_surface(t_line *line, t_cone *cone);

//parsing/line_x_cone_2_1_surface_intersection.c
t_points			intersection(t_line *line, t_cone *cone);
double				cal_stuff(t_cal_helper *h, t_line *line, t_cone *cone);
t_points			intersection2_2(double t, double delta, t_line *line,
						t_cal_helper *h);
t_points			intersection2(double delta, t_line *line, t_cal_helper *h);
t_points			intersection1(t_line *line, t_cal_helper *h);

//parsing/line_x_cone_2_2_color.c 
t_point_nvec		cone_and_texture2(t_point_nvec *ret, t_cone *cone);
t_point_nvec		color_decide2(t_point_nvec *ret, t_cone *cone);

//parsing/parse_a.c
int					get_first_arg(t_data *data, char **splited);
int					set_color_a(t_data *data, char *number, int ind);
int					get_second_arg_a(t_data *data, char **splited);
int					parse_a(t_data *data, char **splited);

//parsing/parse_c.c 
void				error_message_parse_c(int update);
int					get_fov(t_data *data, char *str);
int					set_pos_c(t_data *data, char *number, int ind, int update);
int					get_first_arg_c(t_data *data, char *str, int update);
int					parse_c(t_data *data, char **splited);

//parsing/parse_co.c
int					get_radius_co(char *number, t_cone *cone, int update);
void				helper_co(double *pos, char *number);
int					set_pos_co(char *number, int ind, int update, t_cone *cone);
int					get_first_arg_co(char *str, int update, t_cone *cone);
int					parse_co(t_data *data, char **splited);

//parsing/parse_cy.c
int					get_radius_cy(char *number, t_cylinder *cylinder,
						int update);
void				helper_cy(double *pos, char *number);
int					set_pos_cy(char *number, int ind, int update,
						t_cylinder *cylinder);
int					get_first_arg_cy(char *str, int update,
						t_cylinder *cylinder);
int					parse_cy(t_data *data, char **splited);

//parsing/parse_l.c
void				error_message_parse_l(int update);
int					set_pos_l(t_light *light, char *number, int ind,
						int update);
int					get_first_arg_l(t_light *light, char *str, int update);
int					get_ratio(t_light *light, char *number);
int					parse_l(t_data *data, char **splited);

//parsing/parse_pl.c
void				error_message_parse_pl(int update);
void				helper_pl(double *pos, char *number);
int					set_pos_pl(char *number, int ind, int update,
						t_plane *plane);
int					get_first_arg_pl(char *str, int update, t_plane *plane);
int					parse_pl(t_data *data, char **splited);

//parsing/parse_sp.c 
void				error_message_parse_sp(int update);
int					set_pos_sp(char *number, int ind, int update,
						t_sphere *sphere);
int					get_first_arg_sp(char *str, int update, t_sphere *sphere);
int					get_radius_sp(char *number, t_sphere *sphere);
int					parse_sp(t_data *data, char **splited);

//parsing/parse.c
void				error_not_valid_identifier(char *str);
int					detect_type(t_data *data, char **splited);
int					parse_line(t_data *data, char *line);
int					parse(t_data *data);

/*********************************************************************/
/**************************** textureing *****************************/
/*********************************************************************/
//textureing/cylinder_texture.c
t_vec3				cy_x_checker_side(t_cylinder *cy, t_vec3 *p);
t_vec3				cy_x_texture_bottom(t_cylinder *cy, t_vec3 *p, int type);
t_vec3				cy_x_texture_side(t_cylinder *cy, t_vec3 *p);
t_vec3				apply_texture_cylinder2(t_cylinder *cy, t_vec3 p,
						t_hit *hit);
t_vec3				apply_texture_cylinder(t_hit *hit);

//textureing/cylinder_texture2.c 
t_vec3				find_point_in_bottom_cylinder(t_vec3 *p, t_plain *pl,
						t_vec3 *norm);
t_abc				cal_abc_cy(t_line *li, double r);
void				cylinder_x_plain(t_cylinder *cy, t_vec3 *vab);
double				distance_p_pl(t_vec3 *p, t_plain *pl);
t_vec3				cy_x_checker_bottom(t_cylinder *cy, t_vec3 *p, int type);

//textureing/plane_texture.c
t_vec3				get_vec3(t_hit *hit);
//void	fill_vars(t_many_vars *vars);
//void	calculate_uv(t_many_vars *vars, double *u, double *v);
void				get_uv_plane(t_hit *hit, double *u, double *v);
t_vec3				apply_texture_plane(t_hit *hit);

//textureing/sphere_texture.c 
void				modify_values(mlx_texture_t *texture, int *pixel_x,
						int *pixel_y);
t_vec3				apply_texture_sphere(t_hit *hit);

/*********************************************************************/
/****************************** utils ********************************/
/*********************************************************************/
//utils/free_data.c
void				clean_textures(t_data *data);
void				free_data_before_display(t_data *data);
void				freeing(char **arr);

//utils/ft_split.c
char				**ft_split(char const *s, char c);

//utils/str_to_double.c
double				int_double_notvalid(char *str, int seen, int seen_other);
int					get_sign(char *str, int *move);
long long			str_to_long_long(char *str);
double				str_to_double(char *str);

//utils/utils1.c
int					str_len(char *str);
int					ends_with(char *main, char *sub);
void				change_new_line(char *str);
void				change_app(char *str, char from, char to);
int					is_white_space(char c);

//utils/utils2.c
void				delete_useless_spaces(char *str);
void				display_error_message(char *str);
int					str_compare(char *str1, char *str2);
int					len2d_array(char **arr);
int					get_pos_of_char(char *str, char c);

//utils/utils3.c
void				copy_all_stuff(void *to, void *from, int len);

/*********************************************************************/
/****************************** main* ********************************/
/*********************************************************************/
//main.c
int					get_fd(char *path);
void				init_data(t_data *data, int fd);
#endif
