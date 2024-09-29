/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.check_point_inside_triangle.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:10:46 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 23:22:45 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

typedef struct s_is_inside_triangle2
{
	double	a;
	double	b;
	double	xAB;
	double	xAC;
	double	xAD;
	double	yAB;
	double	yAC;
	double	yAD;
}	t_is_inside_triangle2;

// x -> 1, y -> 2, z-3
static int choose_2_coordinations(t_triangle tri)
{
	if (tri.p1.x == tri.p2.x && tri.p1.x == tri.p3.x)
		return (1);
	if (tri.p1.y == tri.p2.y && tri.p1.y == tri.p3.y)
		return (2);
	return (3);
}

static t_triangle	create_new_4_points_2D(t_point p, t_triangle tri, int not_choose, t_point *p_2D)
{
	if (not_choose == 1)
	{
		tri.p1.x = tri.p1.y;
		tri.p1.y = tri.p1.z;
		tri.p2.x = tri.p2.y;
		tri.p2.y = tri.p2.z;
		tri.p3.x = tri.p3.y;
		tri.p3.y = tri.p3.z;
		p_2D->x = p.y;
		p_2D->y = p.z;
	}
	if (not_choose == 2)
	{
		tri.p1.y = tri.p1.z;
		tri.p2.y = tri.p2.z;
		tri.p3.y = tri.p3.z;
		p_2D->y = p.z;
	}
	return (tri);
}

static int	is_inside_triangle2(t_triangle tri_2D, t_point p_2D)
{
	t_is_inside_triangle2 q;

	q.xAB = tri_2D.p2.x - tri_2D.p1.x;
	q.xAC = tri_2D.p3.x - tri_2D.p1.x;
	q.xAD = p_2D.x - tri_2D.p1.x;
	q.yAB = tri_2D.p2.y - tri_2D.p1.y;
	q.yAC = tri_2D.p3.y - tri_2D.p1.y;
	q.yAD = p_2D.y - tri_2D.p1.y;
	q.b = (q.yAD * q.xAB - q.xAD * q.yAB) / (q.yAC * q.xAB - q.xAC * q.yAB);
	q.a = (q.yAD / q.yAB) - (q.yAC / q.yAB) * q.b;
	if (q.a >= 0 && q.b >= 0 && q.a + q.b <= 1)
		return (1);
	return (0);
}

//use when know a point is on the plain of triangle
int is_inside_triangle(t_point p, t_triangle tri)
{
	int not_choose_coordinations;
	t_triangle triangle_2D;
	t_point p_2D;

	not_choose_coordinations = choose_2_coordinations(tri);
	triangle_2D = create_new_4_points_2D(p, tri, not_choose_coordinations, &p_2D);
	return (is_inside_triangle2(triangle_2D, p_2D));
}
