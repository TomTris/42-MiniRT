/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 16:36:47 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <sys/time.h>


# define TOLARANCE 0.03
# define HEIGHT 1024
# define WIDTH 1024

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

	t_vec3	vec3_cords;
	t_vec3	vec3_color;
}	t_sphere;

typedef struct s_plane
{
	double	cords[3];
	double	vector[3];
	int		colors[3];

	t_vec3	vec3_cords;
	t_vec3	vec3_color;
	t_vec3	vec3_norm;
}	t_plane;

typedef struct s_cylinder
{
	int		colors[3];
	double	diameter;
	double	cords[3];
	double	vector[3];
	double	height;

	t_vec3	vec3_cords;
	t_vec3	vec3_norm;
	t_vec3	vec3_color;
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
}	t_cone;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	int					displayed;

	t_camera			camera;
	t_ambitient_light	ambitient_light;
	t_light				light;

	int					seen_camera;
	int					seen_ambitient_light;
	int					seen_light;

	t_sphere			*spheres;
	t_cylinder			*cylinders;
	t_plane				*planes;
	t_cone				*cones;

	int					amount_of_spheres;
	int					amount_of_cylinders;
	int					amount_of_planes;
	int					amount_of_cones;

	int					fd;
}	t_data;

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

}	t_hit;


//display/display.c
//display/display2.c
uint32_t	per_pixel(t_data *data, t_ray *ray, uint32_t x, uint32_t y);
int	displaying(t_data *data);
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

t_vec3		calculate_light(t_data *data, t_ray *ray, t_hit *hit);
#endif