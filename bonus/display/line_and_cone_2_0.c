/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_2_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:42:31 by qdo               #+#    #+#             */
/*   Updated: 2024/09/30 17:48:51 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_plain	plain_of_bottom_area(t_cone_tom *cone)
{
	t_plain	plain;

	plain.a = cone->vao.x;
	plain.b = cone->vao.y;
	plain.c = cone->vao.z;
	plain.d = - (plain.a * cone->po.x \
				+ plain.b * cone->po.y \
				+ plain.c * cone->po.z);
	return (plain);
}

int	is_point_in_circle(t_cone_tom *cone, t_point *p)
{
	if (cone->r >= sqrt(pow(cone->po.x - p->x, 2) \
				+ pow(cone->po.y - p->y, 2) \
				+ pow(cone->po.z - p->z, 2)))
		return (1);
	return (0);
}

int	is_same_side(t_plain *pl, t_point p1, t_point p2)
{
	double	value1;
	double	value2;

	value1 = pl->a * p1.x + pl->b * p1.y + pl->c * p1.z + pl->d;
	value2 = pl->a * p2.x + pl->b * p2.y + pl->c * p2.z + pl->d;
	if (value1 * value2 > 0)
		return (1);
	return (0);
}

t_point_x_nor_vec	line_x_cone_bottom(t_line *li, t_cone_tom *cone)
{
	t_plain				pl;
	t_point_x_nor_vec	ret;
	double				divided_num;
	t_point				point;

	pl = plain_of_bottom_area(cone);
	divided_num = (pl.a * li->dv.x + pl.b * li->dv.y + pl.c * li->dv.z);
	if (divided_num == 0)
		return (line_parallel_in_plain(&pl, li, cone));
	if (is_same_side(&pl, li->p, cone->pa) == 1)
		return (ret.amount = 0, ret);
	ret.t = - (pl.d + pl.a * li->p.x + pl.b * li->p.y + pl.c * li->p.z) \
			/ divided_num;
	if (ret.t < 0)
		return (ret.amount = 0, ret);
	point.x = li->p.x + li->dv.x * ret.t;
	point.y = li->p.y + li->dv.y * ret.t;
	point.z = li->p.z + li->dv.z * ret.t;
	if (is_point_in_circle(cone, &point))
		return (ret.amount = 1, ret.v = cone->vao, ret);
	return (ret.amount = 0, ret);
}
