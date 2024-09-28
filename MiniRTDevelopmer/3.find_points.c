/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.find_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:34:04 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 21:37:09 by qdo              ###   ########.fr       */
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

t_point	point_from_line_and_bottom_cirle(t_plain pl, t_line line)
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
