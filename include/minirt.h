/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 15:21:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// #include <gperftools/profiler.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <sys/time.h>
# include <pthread.h>
# define TOLARANCE 0.03
# define HEIGHT 1024
# define WIDTH 1024
# define AMOUNT_OF_THREADS 6

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
	int		colors[3];
	double	diameter;
	double	cords[3];

	mlx_texture_t	*texture;
	t_vec3	vec3_cords;
	t_vec3	vec3_color;
	int		checkers;
}	t_sphere;

typedef struct s_plane
{
	double	cords[3];
	double	vector[3];
	int		colors[3];

	mlx_texture_t	*texture;
	t_vec3	vec3_cords;
	t_vec3	vec3_color;
	t_vec3	vec3_norm;
	double	dist;
	int		checkers;
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
	int		colors[3];
	double	diameter;
	double	cords[3];
	double	vector[3];
	double	height;
	int		checkers;

	mlx_texture_t	*texture;
	t_vec3	vec3_cords;
	t_vec3	vec3_norm;
	t_vec3	vec3_color;

	t_vec3	pa;
	t_vec3	pb;
	t_plain	pl_top;
	t_vec3	bottom_ori_vec;
	t_vec3	bottom_ori_vec2;
	t_vec3	vab;
	
	double	r;
}	t_cylinder;


typedef struct s_cone
{
	int		colors[3];
	double	diameter;
	double	cords[3];
	double	vector[3];
	double	height;

	t_vec3	vec3_cords;
	t_vec3	vec3_norm;
	t_vec3	vec3_color;
	int		checkers;
	mlx_texture_t	*texture;

	t_vec3	vao;
	t_vec3	pa;
	t_vec3	po;
	double	r;
	t_plain				pl;
	double	value1;
	double	s;
	double	cos_al;
	double	bottom_width;
	t_vec3	bottom_ori_vec;
	t_vec3	bottom_ori_vec2;
	double	bottom_angle;
	double	bottom_angle_2;
	double	surface_width;
}	t_cone;


typedef struct s_point_x_nor_vec
{
	int		amount;
	double	t;
	t_vec3	v;
	t_vec3	p;
	t_vec3	color;
}	t_point_x_nor_vec;

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
} t_cal_helper;

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
	mlx_texture_t *				texture;
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


//display/display.c
//display/display2.c
void		*displaying(void *input);
void	display(t_data *data);
int	transform_to_channel(double v);
uint32_t	get_color_from_vec3(t_vec3 vec);
void	closest_hit2(t_data *data, t_ray *ray, t_hit *hit);
void	closest_hit(t_data *data, t_ray *ray, t_hit *hit);
void	ray_trace(t_data *data, t_ray *ray, t_hit *hit);

char		*get_next_line(int fd, int *finished);
int			str_len(char *str);
int			ends_with(char *main, char *sub);
void		free_data_before_display(t_data *data);
int			parse(t_data *data);
void		change_new_line(char *str);
void		change_app(char *str, char from, char to);
int			is_white_space(char c);
void		delete_useless_spaces(char *str);
char		**ft_split(char const *s, char c);
void		display_error_message(char *str);
void		freeeing(char **arr);
int			str_compare(char *str1, char *str2);
int			len2d_array(char **arr);
double		int_double_notvalid(char *str, int seen, int seen_other);
long long	str_to_long_long(char *str);
int			get_sign(char *str, int *move);
double		str_to_double(char *str);
int			get_pos_of_char(char *str, char c);
void		freeing(char **arr);

void		copy_all_stuff(void *to, void *from, int len);
int			parse_l(t_data *data, char **splited);
void		output_data(t_data	*data);
void		error_message_parse_cy(int update);
void		error_message_parse_co(int update);

int			parse_a(t_data *data, char **splited);
int			parse_c(t_data *data, char **splited);
int			parse_l(t_data *data, char **splited);
int			parse_sp(t_data *data, char **splited);
int			parse_pl(t_data *data, char **splited);
int			parse_cy(t_data *data, char **splited);
int			parse_co(t_data *data, char **splited);

void		set_null(mlx_texture_t **texture, int *checkers);
int			open_texture(mlx_texture_t **texture, char **path);
int			check_if_ok(t_data *data);
double		get_len_vector_d(double *vector);

void		display(t_data *data);
void		ft_hook_keys(void *param);
void		change_image_size_hook(void *param);
void		make_image_black(mlx_image_t *image);
// int			displaying(t_data *data);
uint32_t	get_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// math
t_vec3		cross(t_vec3 vec1, t_vec3 vec2);
t_vec3		add(t_vec3 vec1, t_vec3 vec2);
t_vec3		subtract(t_vec3 vec1, t_vec3 vec2);
t_vec3		scale(t_vec3 vec, double scale);
t_vec3		normalize(t_vec3 vec);
t_vec3		vec_reflect_norm(t_vec3 vector, t_vec3 reflected_around);
double		dot_product(t_vec3 vec1, t_vec3 vec2);
t_vec3		create_vec3(double x, double y, double z);
t_vec3		apply_matrix(t_vec3 vec, t_matrix3 *matrix);
t_matrix3	create_matrix(t_vec3 axis, double angle);
t_vec3		create_vec3_arr(double *vec);
t_vec3		create_vec3_color_arr(int *arr);
t_vec3		multiply_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3		shrink_vec3(t_vec3 vec, double min, double max);

void		calculate_up(t_data *data);
t_vec3		get_direction_ray(t_data *data, double offset_x, double offset_y);
int			are_vectors_similar(t_vec3 vec1, t_vec3 vec2);

double		max_double(double v1, double v2);
double		min_double(double v1, double v2);
double		square(double number);

long long	get_current_time(void);
void		handle_spheres(t_data *data, t_ray *ray, t_hit *hit);
void		handle_cylinders(t_data *data, t_ray *ray, t_hit *hit);
void		handle_planes(t_data *data, t_ray *ray, t_hit *hit);
void		handle_cones(t_data *data, t_ray *ray, t_hit *hit);
double		get_factor(t_vec3 *norm, t_vec3	*point, t_vec3 *camera);

t_vec3		calculate_light(t_data *data, t_ray *ray, t_hit *hit);

//line_and_cone_1_1.c
t_point_x_nor_vec	line_x_cone(t_line *line, t_cone *cone);
//line_and_cone_1_2.c
t_point_x_nor_vec		line_x_cone_surface1(t_cone *cone, t_points *points, double s);
void					line_x_cone_surface2_2(t_vec3 *cp, t_cone *cone, t_points *points, double s);
t_point_x_nor_vec		line_x_cone_surface2(t_line *line, t_cone *cone, t_points *points, double s);
t_point_x_nor_vec		line_x_cone_surface(t_line *line, t_cone *cone);
//line_and_cone_1_3.c
t_points				intersection2_2(double t, double delta, t_line *line, t_cal_helper *h);
t_points				intersection2(double delta, t_line *line, t_cal_helper *h);
t_points				intersection1(t_line *line, t_cal_helper *h);
	//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
double					cal_stuff(t_cal_helper *h, t_line *line, t_cone *cone);
t_points				intersection(t_line *line, t_cone *cone);
//line_and_cone_2_0.c
// t_plain					plain_of_bottom_area(t_cone *cone);
int				 		is_point_in_circle(t_cone *co, t_vec3 *p);
int	is_same_side(t_plain *pl, t_vec3 p1, double value1);
t_point_x_nor_vec		line_x_cone_bottom(t_line *li, t_cone *cone);
//line_and_cone_2_1.c
t_abc				 	cal_abc(t_line *li, t_cone *cone);
void					line_parallel_in_plain2(t_point_x_nor_vec *ret, t_line *li, t_cone *cone);
t_point_x_nor_vec		line_parallel_in_plain(t_plain *pl, t_line *li, t_cone *cone);
//line_and_cone_2_2.c
double					 dot_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3					vector_p1_to_p2(t_vec3 point1, t_vec3 point2);
double					cal_distance(t_vec3 p1, t_vec3 p2);
double					degree_2_vector(t_vec3 *v1, t_vec3 *v2);
t_vec3					vector_cross_product(t_vec3 v1, t_vec3 v2);
void					calculate_cone(t_cone *cone);


t_vec3	get_color(t_hit *hit);
void	modify_values(mlx_texture_t *texture, int *pixel_x, int *pixel_y);
void	get_uv_plane(t_hit *hit, double *u, double *v);
double alpha_2_vector(t_vec3 *v1, t_vec3 *v2);
double cos_alpha_2_vector(t_vec3 *v1, t_vec3 *v2);
t_vec3	apply_texture_plane(t_hit *hit);
t_vec3	apply_texture_sphere(t_hit *hit);
int	check_planes(t_data *data, int i);
int	check_is_vector_ok(double *vector);
void	set_type_distance_cy2(t_hit *hit, double dist, int var);
double value_a_vector(t_vec3 vec);
t_vec3	apply_texture_cylinder(t_hit *hit);
double	vector_length(t_vec3 v);
#endif