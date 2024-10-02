/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_2_0_surface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:43:08 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 15:40:59 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_point_x_nor_vec	line_x_cone_surface1(t_cone *cone,
	t_points *points, double s)
{
	t_vec3				cp;
	t_vec3				ap;
	t_vec3				op;
	t_point_x_nor_vec	ret;

	cp.x = points->p1.x - cone->pa.x;
	cp.y = points->p1.y - cone->pa.y;
	cp.z = points->p1.z - cone->pa.z;
	if (degree_2_vector(&cp, &cone->vao) > M_PI_2 \
		|| cal_distance(points->p1, cone->pa) > s)
		return (ret.amount = 0, ret);
	ret.amount = 1;
	ret.t = points->t1;
	ap = vector_p1_to_p2(cone->pa, points->p1);
	op = vector_p1_to_p2(cone->po, points->p1);
	ret.v = vector_cross_product(vector_cross_product(ap, op), ap);
	ret.v = normalize(ret.v);
	if (dot_vec(ret.v, op) < 0)
	{
		ret.v.x *= -1;
		ret.v.y *= -1;
		ret.v.y *= -1;
	}
	ret.p = points->p1;
	return (color_decide2(&ret, cone));
}

void	line_x_cone_surface2_2(t_vec3 *cp, t_cone *cone,
	t_points *points, double s)
{
	cp->x = points->p2.x - cone->pa.x;
	cp->y = points->p2.y - cone->pa.y;
	cp->z = points->p2.z - cone->pa.z;
	if (degree_2_vector(cp, &cone->vao) > M_PI_2 || \
		cal_distance(points->p2, cone->pa) > s)
		points->amount = 1;
	cp->x = points->p1.x - cone->pa.x;
	cp->y = points->p1.y - cone->pa.y;
	cp->z = points->p1.z - cone->pa.z;
	if (degree_2_vector(cp, &cone->vao) > M_PI_2 || \
		cal_distance(points->p1, cone->pa) > s)
	{
		points->amount -= 1;
		points->p1 = points->p2;
		points->t1 = points->t2;
	}
}

t_point_x_nor_vec	line_x_cone_surface2(t_line *line, \
	t_cone *cone, t_points *points, double s)
{
	t_vec3				ap;
	t_vec3				op;
	t_vec3				cp;
	t_point_x_nor_vec	ret;

	line_x_cone_surface2_2(&cp, cone, points, s);
	if (points->amount == 0)
		return (ret.amount = 0, ret);
	if (points->amount == 2)
	{
		if (cal_distance(points->p1, line->p) \
			> cal_distance(points->p2, line->p))
		{
			points->p1 = points->p2;
			points->t1 = points->t2;
		}
	}
	ap = vector_p1_to_p2(cone->pa, points->p1);
	op = vector_p1_to_p2(cone->po, points->p1);
	ret.v = vector_cross_product(vector_cross_product(ap, op), ap);
	ret.v = normalize(ret.v);
	if (dot_vec(ret.v, op) < 0)
		ret.v = scale(ret.v, -1);
	return (ret.amount = 1, ret.p = points->p1, ret.t = points->t1,
		color_decide2(&ret, cone), ret);
}

t_point_x_nor_vec	line_x_cone_surface(t_line *line, t_cone *cone)
{
	t_points			points;
	t_point_x_nor_vec	ret;

	points = intersection(line, cone);
	if (points.amount == 0)
		return (ret.amount = 0, ret);
	if (points.amount == 1)
		return (line_x_cone_surface1(cone, &points, cone->s));
	return (line_x_cone_surface2(line, cone, &points, cone->s));
}
