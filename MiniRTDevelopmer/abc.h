/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/27 22:59:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;


typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

//ax + by + cz + d = 0
typedef struct s_plain
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_plain;

typedef struct s_line
{
	t_point	point;
	t_vec3	direction_vector;
} t_line;

typedef struct s_triangle
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
} t_triangle;

typedef struct s_cone
{
	t_vec3	vAO;
	t_point	pA;
	t_point	pO;
	double	r;
}	t_cone;


//checker1.c
int				is_valid_vector(t_vec3 vec);
int				is_valid_line(t_line line);
int				is_valid_plain(t_plain plain);
int				is_vector_plain_parallel(t_vec3 vec, t_plain pl);

//checker2.c
int				is_two_vector_same_direction(t_vec3 vec1, t_vec3 vec2);
int				is_valid_cone(t_cone cone);

//checker3.c
int				is_on_plain(t_plain pl, t_point p);

//create_line.c
t_line			line_from_vector_and_point(t_vec3 vec, t_point p);

//create_plain.c
int				are_3_points(t_point point1, t_point point2, t_point point3);
t_plain			plain_from_3_points(t_point p1, t_point p2, t_point p3);
t_plain			plain_of_bottom_area(t_point pO, t_vec3 vAO);

//find_point.c
t_point			point_from_plain_and_line(t_plain pl, t_line line);

//check_point_inside_triangle.c
int				choose_2_coordinations(t_triangle tri);
t_triangle		create_new_4_points_2D(t_point p, t_triangle tri, int not_choose, t_point *p_2D);
int				is_inside_triangle(t_point p, t_triangle tri);

//check_point_inside_bottom_area.c
int				is_point_inside_bottom_area(t_point pA, t_point pO, t_vec3 vAO, double r);

#endif
