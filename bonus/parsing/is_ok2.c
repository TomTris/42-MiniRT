/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/30 20:59:14 by qdo              ###   ########.fr       */
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

void calculate_cone(t_cone *cone)
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
}
