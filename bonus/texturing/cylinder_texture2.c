/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:55:56 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_vec3	find_point_in_bottom_cylinder(t_vec3 *p, t_plain *pl, t_vec3 *norm)
{
	double	t;
	t_vec3	vap;

	t = -(pl->a * p->x + pl->b * p->y + pl->c * p->z + pl->d) / \
		(pl->a * norm->x + pl->b * norm->y + pl->c * norm->z);
	vap.x = p->x + norm->x * t;
	vap.y = p->y + norm->y * t;
	vap.z = p->z + norm->z * t;
	return (vap);
}

t_abc	cal_abc_cy(t_line *li, double r)
{
	t_abc	abc;

	abc.a = pow(li->dv.x, 2) + pow(li->dv.y, 2) + pow(li->dv.z, 2);
	abc.b = 0;
	abc.c = -pow(r, 2);
	return (abc);
}

void	cylinder_x_plain(t_cylinder *cy, t_vec3 *vab)
{
	t_line	li;
	t_abc	abc;
	double	delta;
	double	t;
	t_vec3	intersec;

	if (vab->x == 0.0)
		li.dv = create_vec3(1, 0, 0);
	else if (vab->y == 0.0)
		li.dv = create_vec3(0, 1, 0);
	else if (vab->z == 0.0)
		li.dv = create_vec3(0, 0, 1);
	else
		li.dv = vector_cross_product(*vab, create_vec3(1, 0, 0));
	abc = cal_abc_cy(&li, cy->r);
	delta = sqrt(pow(abc.b, 2) - 4 * abc.a * abc.c);
	t = (-abc.b - delta) / (2 * abc.a);
	intersec.x = cy->pa.x + li.dv.x * t;
	intersec.y = cy->pa.y + li.dv.y * t;
	intersec.z = cy->pa.z + li.dv.z * t;
	cy->bottom_ori_vec = vector_p1_to_p2(cy->pa, intersec);
	cy->bottom_ori_vec2 = vector_cross_product(cy->vab, cy->bottom_ori_vec);
}

double	distance_p_pl(t_vec3 *p, t_plain *pl)
{
	double	ret;

	ret = (pl->a * p->x + pl->b * p->y + pl->c * p->z + pl->d) / \
		(sqrt(pow(pl->a, 2) + pow(pl->b, 2) + pow(pl->c, 2)));
	if (ret < 0)
		ret *= -1;
	return (ret);
}

t_vec3	cy_x_checker_bottom(t_cylinder *cy, t_vec3 *p, int type)
{
	double	temp;
	t_vec3	ox;
	int		color;

	color = 1;
	if (type == 2)
		ox = vector_p1_to_p2(cy->pa, *p);
	else
		ox = vector_p1_to_p2(cy->pb, *p);
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec, &ox);
	if ((int)((temp + cy->r) / cy->diameter * 10) % 2 == 0)
		color = -1;
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec2, &ox);
	if ((int)((temp + cy->r) / cy->diameter * 10) % 2 == 0)
		color *= -1;
	if (color == 1)
		return (create_vec3(1, 1, 1));
	return (cy->vec3_color);
}
