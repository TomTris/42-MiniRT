/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 15:47:41 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_plain	plain_of_bottom_area(t_cone *cone)
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

//use cal_abc_cy // cal_abc_same_point
void	cone_and_bottom(t_cone *cone)
{
	t_line	li;
	t_abc	abc;
	double	delta;
	double	t;
	t_vec3	intersec;

	cone->bottom_width = cone->r / 6;
	cone->bottom_angle = M_PI / 6;
	cone->bottom_angle_2 = M_PI / 12;
	if (cone->vao.x == 0.0)
		li.dv = create_vec3(1, 0, 0);
	else if (cone->vao.y == 0.0)
		li.dv = create_vec3(0, 1, 0);
	else if (cone->vao.z == 0.0)
		li.dv = create_vec3(0, 0, 1);
	else
		li.dv = vector_cross_product(cone->vao, create_vec3(1, 0, 0));
	li.p = cone->po;
	abc = cal_abc(&li, cone);
	delta = sqrt(pow(abc.b, 2) - 4 * abc.a * abc.c);
	t = (-abc.b - delta) / (2 * abc.a);
	intersec.x = li.p.x + li.dv.x * t;
	intersec.y = li.p.y + li.dv.y * t;
	intersec.z = li.p.z + li.dv.z * t;
	cone->bottom_ori_vec = vector_p1_to_p2(cone->po, intersec);
}

void	cone_and_bottom2(t_cone *cone)
{
	cone->bottom_ori_vec2 = \
		vector_cross_product(cone->vao, cone->bottom_ori_vec);
}

void	cone_and_surface(t_cone *cone)
{
	cone->surface_width = cone->s / 10;
}

void	calculate_cone(t_cone *cone)
{
	cone->vao = cone->vec3_norm;
	cone->pa = cone->vec3_cords;
	cone->po = add(cone->vec3_cords, \
		scale(cone->vec3_norm, cone->height));
	cone->r = cone->diameter / 2.0;
	cone->pl = plain_of_bottom_area(cone);
	cone->value1 = cone->pl.a * cone->pa.x + cone->pl.b * cone->pa.y \
		+ cone->pl.c * cone->pa.z + cone->pl.d;
	cone->s = sqrt(pow(cone->r, 2) + \
		pow(cal_distance(cone->pa, cone->po), 2));
	cone->cos_al = cone->height \
		/ sqrt(cone->height * cone->height + cone->r * cone->r);
	cone_and_bottom(cone);
	cone_and_bottom2(cone);
	cone_and_surface(cone);
}
