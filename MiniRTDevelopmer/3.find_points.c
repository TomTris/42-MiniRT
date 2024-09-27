/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.find_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:34:04 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 01:02:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

//find point from plain and line, which has intersection
t_point	point_from_plain_and_line(t_plain pl, t_line line)
{
	double	t;
	t_point	lp;
	t_vec3	lv;
	t_point	ret_p;

	lp = line.point;
	lv = line.direction_vector;
	t = - (pl.d + pl.a * lp.x + pl.b * lp.y + pl.c * lp.z) \
			/ (pl.a * lv.x + pl.b * lv.y + pl.c * lv.z);
	ret_p.x = lp.x + lv.x * t;
	ret_p.y = lp.y + lv.y * t;
	ret_p.z = lp.z + lv.z * t;
	return (ret_p);
}

//find points from plain, which is perpenticular to Light,
//go through A and O of coune.
//these 3 points are point A - top of cone and the other 2
//vector LO, then normalvector(LO, AO), this plain cut bottom area at 2 points
// t_point	*points_of_triangle(t_point light, t_cone cone, int	point_nbr)
// {
// 	t_vec3	vLO;
// 	t_vec3	direction_vector_of_line;


// }

//point_nbr = 1 / 2
t_point	points_with_r_from_O(t_line line, t_point pO, int point_nbr, double r)
{
	t_point	p;
	t_vec3	lv;
	double	sqrt_value;

	lv = line.direction_vector;
	sqrt_value = sqrt(pow(lv.x, 2) + pow(lv.y, 2) + pow(lv.z, 2));
	if (point_nbr == 1)
	{
		p.x = pO.x + (r * lv.x) / sqrt_value;
		p.y = pO.y + (r * lv.y) / sqrt_value;
		p.z = pO.z + (r * lv.z) / sqrt_value;
		return p;
	}
	p.x = pO.x - (r * lv.x) / sqrt_value;
	p.y = pO.y - (r * lv.y) / sqrt_value;
	p.z = pO.z - (r * lv.z) / sqrt_value;
	return p;
}
