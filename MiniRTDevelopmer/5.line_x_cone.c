/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.line_x_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:08:47 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 23:18:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"
typedef struct s_abc
{
	double a;
	double b;
	double c;
} t_abc;


t_abc calculate_for_delta(t_line line, t_cone cone)
{
	t_point	lp = line.point;
	t_vec3	lv = line.direction_vector;
	t_point	cO = cone.pO;
	t_abc	abc;

	abc.a = pow(lv.x, 2) + pow(lv.y, 2) + pow(lv.z, 2);
	abc.b = 2 * (lv.x * (lp.x - cO.x) + lv.y * (lp.y - cO.y) + lv.z * (lp.z - cO.z));
	abc.c = pow(lv.x - cO.x, 2) + (lp.y - cO.y, 2) + (lp.z - cO.z, 2) - pow(cone.r, 2);
	return (abc);
}

int	calculate_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2)));
}

t_points find_points_line_x_circle2(t_points ret, double delta, t_abc abc, t_line line)
{
	double	t1;
	double	t2;

	ret.amount = 2;
	t1 = (- abc.b - sqrt(delta)) / 2 * abc.a;
	t2 = (- abc.b + sqrt(delta)) / 2 * abc.a;
	ret.point1.x = line.point.x + line.direction_vector.x * t1;
	ret.point1.y = line.point.y + line.direction_vector.y * t1;
	ret.point1.z = line.point.z + line.direction_vector.z * t1;
	ret.point2.x = line.point.x + line.direction_vector.x * t2;
	ret.point2.y = line.point.y + line.direction_vector.y * t2;
	ret.point2.z = line.point.z + line.direction_vector.z * t2;
	return (ret);
}

t_points	find_points_line_x_circle(t_line line, t_cone cone)
{
	t_abc 	abc;
	double 	delta;
	t_points	ret;
	double	t;

	abc = calculate_for_delta(line, cone);
	delta = pow(abc.b, 2) - 4 * abc.a * abc.c;
	if (delta < 0)
		return (ret.amount = 0, ret);
	if (delta == 0)
	{
		ret.amount = 1;
		t = - abc.b / 2 * abc.a;
		ret.point1.x = line.point.x + line.direction_vector.x * t;
		ret.point1.y = line.point.y + line.direction_vector.y * t;
		ret.point1.z = line.point.z + line.direction_vector.z * t;
		return (ret);
	}
	return find_points_line_x_circle2(ret, delta, abc, line);
}

t_points line_in_bottom(t_line line, t_cone cone)
{
	t_points points = find_points_line_x_circle(line, cone);
	if (points.amount <= 1)
		return (points);
	points.amount = 1;
	if (calculate_distance(line.point, points.point1) > calculate_distance(line.point, points.point2))
		points.point1 = points.point2;
	return (points);
}
t_plain	plain_of_triangle2(t_cone cone, t_line line)
{
	
}

t_plain	plain_of_triangle(t_cone cone, t_line line)
{
	t_vec3	helper = vector_cross_product(line.direction_vector, cone.vAO);
	return (plain_from_2_vector(helper, cone.vAO, cone.pO));
}

t_points points_expand_from_o(t_line line, t_cone cone)
{
	t_line	new_line;

	new_line.direction_vector = vector_cross_product(line.direction_vector, cone.vAO);
	return (find_points_line_x_circle(new_line, cone));
}

t_points	line_parallel_bottom(t_line line, t_cone cone)
{
	t_plain	triangle_plain = plain_of_triangle(cone, line);
	t_point	point_on_triangle_plain = point_from_plain_and_line(triangle_plain, line);
	t_points	two_points = points_expand_from_o(line, cone);
	t_points	ret;
	t_triangle tri;

	tri.p1 = cone.pA;
	tri.p2 = two_points.point1;
	tri.p3 = two_points.point2;
	if (!is_inside_triangle(point_on_triangle_plain, tri))
	{
		ret.amount = 0;
		return (ret)
	}
}

t_points *point_doesnt_exists()
{
	t_points *ret;
	
	ret = (t_point *)malloc(sizeof(t_points));
	if (ret == 0)
		return (perror("Malloc failed"), NULL);
	ret[0].amount = 0;
	return (ret);
}

t_points	*line_cut_bottom_plain(t_line line, t_plain bottom_plain, t_cone cone)
{
	t_point	intersection = point_from_plain_and_line(bottom_plain, line);
	if (is_point_inside_bottom_area(cone, intersection) == 1)
	{
		t_point point_in_bottom = find_point_inside_bottom_area();
		t_vec3 light_point_vector = vector_AO_form_A_O(line.point, point_in_bottom);
		
		if (angle_vectors(light_point_vector, cone.vAO) > 90)
		{
			t_points	*ret;
			ret = (t_point *)malloc(sizeof(t_points));
			ret[0].amount = 1;
			ret[0].point1 = point_in_bottom;
			return (ret);
		}
		return (point_must_on_side(line, cone));
	}
	t_plain	triangle_plain = create_triangle_plain(line, cone);
	if (does_line_cut_triangle(line, triangle_plain))
		return (point_must_on_side(line, cone));
	return (point_doesnt_exists());
}

//return NULL
//check == 0 -> no points
//check == 1 -> malloc fail
t_points	*point_from_line_x_cone(t_line line, t_cone cone, int *check)
{
	t_plain	bottom_plain = plain_of_bottom_area(cone);
	t_plain	triangle_area;
	int	check;

	check = is_line_parallel_or_in_plain(line, bottom_plain);
	if (check == 1) // in
		return (line_in_bottom(line, cone));
	if (check == 2) //parallel
		return (line_parallel_bottom(line, bottom_plain));
	return (line_cut_bottom_plain(line, bottom_plain, cone));
}
