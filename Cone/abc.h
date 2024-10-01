/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/30 20:08:52 by qdo              ###   ########.fr       */
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

typedef struct s_points
{
	int	amount;
	t_vec3 p1;
	t_vec3 p2;
}	t_points;

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
	t_vec3	p;
	t_vec3	dv;
} t_line;

typedef struct s_triangle
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
} t_triangle;

typedef struct s_cone
{
	t_vec3	vAO;
	t_vec3	pA;
	t_vec3	pO;
	double	r;
}	t_cone;


//checker1.c
int				is_valid_vector(t_vec3 vec);
int				is_valid_line(t_line line);
int				is_valid_plain(t_plain plain);
int				is_vector_plain_parallel(t_vec3 vec, t_plain pl);

//checker2.c
int				is_two_vector_same_direction(t_vec3 vec1, t_vec3 vec2);
int	is_two_vector_parralel(t_vec3 vec1, t_vec3 vec2);
//checker3.c
int				is_on_plain(t_plain pl, t_vec3 p);
int				is_valid_cone(t_cone cone);
int	is_perpenticular(t_vec3 vec1, t_vec3 vec2);
int	is_line_parallel_or_in_plain(t_line line, t_plain pl);
//other_basic.c
t_vec3	vector_cross_product(t_vec3 v1, t_vec3 v2);
t_plain plain_from_2_vector(t_vec3 v1, t_vec3 v2, t_vec3 p);
t_vec3	vector_AO_form_A_O(t_vec3 pA, t_vec3 pO);



int	dot_product(t_vec3 v1, t_vec3 v2);
//create_line.c
t_line			line_from_vector_and_point(t_vec3 vec, t_vec3 p);

//create_plain.c
int				are_3_points(t_vec3 point1, t_vec3 point2, t_vec3 point3);
t_plain			plain_from_3_points(t_vec3 p1, t_vec3 p2, t_vec3 p3);
t_plain			plain_of_bottom_area(t_cone cone);

//find_point.c
t_vec3			point_from_plain_and_line(t_plain pl, t_line line);

//check_point_inside_triangle.c
int				is_inside_triangle(t_vec3 p, t_triangle tri);

//check_point_inside_bottom_area.c
int				is_point_inside_bottom_area(t_cone co, t_vec3 p);

#endif
