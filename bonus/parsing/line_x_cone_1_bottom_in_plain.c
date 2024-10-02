/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_1_bottom_in_plain.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:23:08 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_abc	cal_abc(t_line *li, t_cone *cone)
{
	t_vec3	lp;
	t_vec3	lv;
	t_vec3	co;
	t_abc	abc;

	lp = li->p;
	lv = li->dv;
	co = cone->po;
	abc.a = pow(lv.x, 2) + pow(lv.y, 2) + pow(lv.z, 2);
	abc.b = 2 * \
		(lv.x * (lp.x - co.x) + lv.y * (lp.y - co.y) + lv.z * (lp.z - co.z));
	abc.c = pow(lp.x - co.x, 2) + pow(lp.y - co.y, 2) \
		+ pow(lp.z - co.z, 2) - pow(cone->r, 2);
	return (abc);
}

void	line_parallel_in_plain2(t_point_x_nor_vec *ret,
	t_line *li, t_cone *cone)
{
	ret->amount = 1;
	ret->p.x = li->p.x + li->dv.x * ret->t;
	ret->p.y = li->p.y + li->dv.y * ret->t;
	ret->p.z = li->p.z + li->dv.z * ret->t;
	ret->v = normalize(vector_p1_to_p2(cone->po, ret->p));
}

t_point_x_nor_vec	line_parallel_in_plain(t_plain *pl, t_line *li,
	t_cone *cone)
{
	t_point_x_nor_vec	ret;
	t_abc				abc;
	double				delta;

	if (pl->a * li->p.x + pl->b * li->p.y + pl->c * li->p.z + pl->d != 0)
		return (ret.amount = 0, ret);
	abc = cal_abc(li, cone);
	delta = pow(abc.b, 2) - 4 * abc.a * abc.c;
	if (delta < 0)
		return (ret.amount = 0, ret);
	delta = sqrt(delta);
	ret.t = (-abc.b - delta) / (2 * abc.a);
	if (ret.t < 0)
	{
		ret.t = (-abc.b + delta) / (2 * abc.a);
		if (ret.t < 0)
			return (ret.amount = 0, ret);
	}
	line_parallel_in_plain2(&ret, li, cone);
	return (ret);
}
