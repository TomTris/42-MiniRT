/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_0_vector_related1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:24:10 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 15:45:53 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	alpha_2_vector(t_vec3 *v1, t_vec3 *v2)
{
	double	top;
	double	down;

	top = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	down = sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) \
		* sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
	return (acos(top / down));
}

double	cos_alpha_2_vector(t_vec3 *v1, t_vec3 *v2)
{
	double	top;
	double	down;

	top = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	down = sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) \
		* sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
	return (top / down);
}

double	vector_length(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double	value_a_vector(t_vec3 vec)
{
	return (vec.x + vec.y + vec.z);
}

//gimme 2 point a b, return point at plain with that vector
//a and b are not together in plain
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
