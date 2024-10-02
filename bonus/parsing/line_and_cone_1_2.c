/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_1_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:43:08 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 10:45:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	find_point_in_bottom(t_vec3 *p, t_plain *pl, t_vec3 *a)
{
	double	t;
	t_vec3	vap;

	vap.x = p->x - a->x;
	vap.y = p->y - a->y;
	vap.z = p->z - a->z;
	t = -(pl->a * p->x + pl->b * p->y + pl->c * p->z + pl->d) / \
		(pl->a * vap.x + pl->b * vap.y + pl->c * vap.z);
	vap.x = p->x + vap.x * t;
	vap.y = p->y + vap.y * t;
	vap.z = p->z + vap.z * t;
	return (vap);	
}

double value_a_vector(t_vec3 vec)
{
	return (vec.x + vec.y + vec.z);
}

t_point_x_nor_vec	cone_and_texture2(t_point_x_nor_vec *ret, t_cone *cone)
{
	int	height;
	t_vec3	point_in_bottom;
	double	alpha;
	t_vec3	ox;
	int	width;

	height = ((cal_distance(cone->pa, ret->p)) / cone->s) \
			* cone->texture->height;
	point_in_bottom = find_point_in_bottom(&ret->p, &cone->pl, &cone->pa);
	ox = vector_p1_to_p2(cone->po, point_in_bottom);
	alpha = alpha_2_vector(&ox, &cone->bottom_ori_vec);
	if (value_a_vector(vector_cross_product(cone->bottom_ori_vec, ox)) <0)
		alpha = 2 * M_PI - alpha;
	alpha /= (2 * M_PI);
	width = (int)(alpha * cone->texture->width);
	ret->color.x = \
		(double)cone->texture->pixels[((height \
		* cone->texture->width + width) * 4)] / 255.0;
	ret->color.y = \
		(double)cone->texture->pixels[((height * \
		cone->texture->width + width) * 4 + 1)] / 255.0;
	ret->color.z = \
		(double)cone->texture->pixels[((height * \
		cone->texture->width + width) * 4 + 2)] / 255.0;
	return (*ret);
}

t_point_x_nor_vec	color_decide2(t_point_x_nor_vec *ret, t_cone *cone)
{
	int	color;
	t_vec3	point_in_bottom;
	double	alpha;
	t_vec3	ox;
	
	if (cone->texture != 0)
		return (cone_and_texture2(ret, cone));
	if (cone->checkers == 0)
		return (ret->color = cone->vec3_color, *ret);
	color = 1;
	if ((int) (cal_distance(cone->pa, ret->p) / cone->surface_width) % 2 == 1)
		color *= -1;
	point_in_bottom = find_point_in_bottom(&ret->p, &cone->pl, &cone->pa);
	ox = vector_p1_to_p2(cone->po, point_in_bottom);
	alpha = alpha_2_vector(&ox, &cone->bottom_ori_vec);
	if ((int)((alpha + cone->bottom_angle_2) / cone->bottom_angle) % 2 == 1)
		color *= -1;
	if (color == 1)
		ret->color = cone->vec3_color;
	else
		ret->color = create_vec3(1, 1, 1);
	return (*ret);
}

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
