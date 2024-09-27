/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain_from_3_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:56:03 by qdo               #+#    #+#             */
/*   Updated: 2024/09/26 22:41:38 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

int is_plane_invalid(t_plane plane)
{
	if (plane.a == 0 && plane.b == 0 && plane.c == 0 && plane.d == 0)
		return (perror("Plane invalid"), 0);
	return (1);
}

int is_line_valid(t_line line)
{
	if (line.direction_vector.x == 0 
		&& line.direction_vector.y == 0 
		&& line.direction_vector.z == 0)
		return (perror("Plane invalid"), 0);
	return (1);
}

int are_3_points(t_point point1, t_point point2, t_point point3)
{
	if (point1.x == point2.x && point1.y == point2.y && point1.z == point2.z)
		return (0);
	if (point1.x == point3.x && point1.y == point3.y && point1.z == point3.z)
		return (0);
	if (point3.x == point2.x && point3.y == point2.y && point3.z == point2.z)
		return (0);
	return (1);
}

t_plane plane_from_3_points(t_point p1, t_point p2, t_point p3)
{
	t_plane plane;

	plane.a = 0;
	plane.b = 0;
	plane.c = 0;
	plane.d = 0;
	if (are_3_points(p1, p2, p3) == 0)
		return (perror("Not 3 different points"), plane);
	plane.a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
	plane.b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z);
	plane.c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	plane.d = -(plane.a * p1.x + plane.b * p1.y + plane.c * p1.z);
	return (plane);
}

t_line line_from_vector_and_point(t_vec3 vec, t_point p)
{
	t_line line;

	line.direction_vector.x = 0;
	line.direction_vector.y = 0;
	line.direction_vector.z = 0;
	line.point.x = 0;
	line.point.y = 0;
	line.point.z = 0;
	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		return (perror("Invalid Vector"), line);
	line.direction_vector = vec;
	line.point = p;
	return (line);
}

int is_on_plane(t_plane pl, t_point p)
{
	if (pl.a * p.x + pl.b * p.y + pl.c + p.z + pl.d == 0)
		return (1);
	return (0);
}

// x -> 1, y -> 2, z-3
int choose_2_coordinations(t_triangle tri)
{
	if (tri.p1.x == tri.p2.x && tri.p1.x == tri.p3.x)
		return (1);
	if (tri.p1.y == tri.p2.y && tri.p1.y == tri.p3.y)
		return (2);
	return (3);
}

t_triangle	create_new_4_points_2D(t_point p, t_triangle tri, int not_choose, t_point *p_2D)
{
	if (not_choose == 1)
	{
		tri.p1.x = tri.p1.y;
		tri.p1.y = tri.p1.z;
		tri.p2.x = tri.p2.y;
		tri.p2.y = tri.p2.z;
		tri.p3.x = tri.p3.y;
		tri.p3.y = tri.p3.z;
		p_2D->x = p_2D->y;
		p_2D->y = p_2D->z;
	}
	if (not_choose == 2)
	{
		tri.p1.y = tri.p1.z;
		tri.p2.y = tri.p2.z;
		tri.p3.y = tri.p3.z;
		p_2D->y = p_2D->z;
	}
	return (tri);
}

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

int	is_inside_triangle2(t_triangle tri_2D, t_point p_2D)
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

int is_inside_triangle(t_point p, t_triangle tri)
{
	t_plane pl;
	int not_choose_coordinations;
	t_triangle triangle_2D;
	t_point p_2D;

	pl = plane_from_3_points(tri.p1, tri.p2, tri.p3);
	if (!is_plane_invalid(pl))
		return (0);
	if (!is_on_plane(pl, p))
		return (0);
	not_choose_coordinations = choose_2_coordinations(tri);
	triangle_2D = create_new_4_points_2D(p, tri, not_choose_coordinations, &p_2D);
	return (is_inside_triangle2(triangle_2D, p_2D));
}

int	is_inside_