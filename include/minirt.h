/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/17 21:43:03 by obrittne         ###   ########.fr       */
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

typedef struct s_camera
{
	double	cords[3];
	double	vector[3];
	int		fov;
}	t_camera;


typedef struct s_ambitient_light
{
	double	colors[3];
	double	ratio;
}	t_ambitient_light;


typedef struct s_light
{
	double	colors[3];
	double	ratio;
	double	cords[3];
}	t_light;


typedef struct s_sphere
{
	double	colors[3];
	double	diameter;
	double	cords[3];
}	t_sphere;


typedef struct s_plane
{
	double	cords[3];
	double	vector[3];
	double	colors[3];
}	t_plane;


typedef struct s_cylinder
{
	double	colors[3];
	double	diameter;
	double	cords[3];
	double	vector[3];
	double	height;
}	t_cylinder;


typedef struct s_cone
{
	double	colors[3];
	double	diameter;
	double	cords[3];
	double	vector[3];
	double	height;
}	t_cone;



typedef struct s_data
{
	mlx_t				*mlx;

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
int			parse_c(t_data *data, char **splited);
int			parse_a(t_data *data, char **splited);
#endif