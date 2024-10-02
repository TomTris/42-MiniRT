/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_2_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:16:37 by qdo               #+#    #+#             */
/*   Updated: 2024/09/30 20:08:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	dot_vec(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vector_p1_to_p2(t_vec3 point1, t_vec3 point2)
{
	t_vec3	vec;

	vec.x = point2.x - point1.x;
	vec.y = point2.y - point1.y;
	vec.z = point2.z - point1.z;
	return (vec);
}

double	cal_distance(t_vec3 p1, t_vec3 p2)
{
	return (sqrt(\
		pow(p1.x - p2.x, 2) \
		+ pow(p1.y - p2.y, 2) \
		+ pow(p1.z - p2.z, 2)));
}

double	degree_2_vector(t_vec3 *v1, t_vec3 *v2)
{
	return (acos(\
		(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) \
			/ (sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z) \
				+ sqrt(v2->x * v2->x + v2->y * v2->y + v2->z * v2->z))));
}

t_vec3	vector_cross_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}
