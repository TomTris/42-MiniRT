/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 18:13:34 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_point_x_nor_vec
{
	int	amount;
	double	t;
	t_vec3	v;
} t_point_x_nor_vec;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_points
{
	int	amount;
	t_point p1;
	t_point p2;
	double	t1;
	double	t2;
}	t_points;

typedef struct s_line
{
	t_point	p;
	t_vec3	dv;
} t_line;

typedef struct s_cone
{
	t_vec3	vAO;
	t_point	pA;
	t_point	pO;
	double	r;
}	t_cone;

#endif
