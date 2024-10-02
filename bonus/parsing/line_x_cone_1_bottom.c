/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_1_bottom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:42:31 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

int	is_point_in_circle(t_cone *cone, t_vec3 *p)
{
	if (cone->r >= sqrt(pow(cone->po.x - p->x, 2) \
				+ pow(cone->po.y - p->y, 2) \
				+ pow(cone->po.z - p->z, 2)))
		return (1);
	return (0);
}

int	is_same_side(t_plain *pl, t_vec3 p1, double value1)
{
	double	value2;

	value2 = pl->a * p1.x + pl->b * p1.y + pl->c * p1.z + pl->d;
	if (value1 * value2 > 0)
		return (1);
	return (0);
}

t_point_x_nor_vec	line_x_cone_bottom(t_line *li, t_cone *cone)
{
	t_point_x_nor_vec	ret;
	double				divided_num;

	divided_num = (cone->pl.a * li->dv.x + cone->pl.b \
		* li->dv.y + cone->pl.c * li->dv.z);
	if (divided_num == 0)
		return (line_parallel_in_plain(&cone->pl, li, cone));
	if (is_same_side(&cone->pl, li->p, cone->value1) == 1)
		return (ret.amount = 0, ret);
	ret.t = - (cone->pl.d + cone->pl.a * li->p.x + cone->pl.b \
		* li->p.y + cone->pl.c * li->p.z) / divided_num;
	if (ret.t < 0)
		return (ret.amount = 0, ret);
	ret.p.x = li->p.x + li->dv.x * ret.t;
	ret.p.y = li->p.y + li->dv.y * ret.t;
	ret.p.z = li->p.z + li->dv.z * ret.t;
	if (is_point_in_circle(cone, &ret.p))
		return (ret.amount = 1, ret.v = cone->vao, ret);
	return (ret.amount = 0, ret);
}
