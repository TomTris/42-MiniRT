/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/25 21:15:26 by qdo              ###   ########.fr       */
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
typedef struct s_plane
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_plane;

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

#endif