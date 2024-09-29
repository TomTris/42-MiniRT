/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.create_plain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:07:07 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 00:50:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

//Create a plain from 3 valid points
t_plain plain_from_3_points(t_point p1, t_point p2, t_point p3)
{
	t_plain plain;

	plain.a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
	plain.b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z);
	plain.c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	plain.d = -(plain.a * p1.x + plain.b * p1.y + plain.c * p1.z);
	return (plain);
}

//Create the plain of bottom area from a valid cone
t_plain plain_of_bottom_area(t_cone cone)
{
	t_plain	plain;

	plain.a = cone.vAO.x;
	plain.b = cone.vAO.y;
	plain.c = cone.vAO.z;
	plain.d = - (plain.a * cone.pO.x \
				+ plain.b * cone.pO.y \
				+ plain.c * cone.pO.z);
	return (plain);
}

//Creat the plain from 2 lines, which cut each other
t_plain plain_from_2_vector(t_vec3 v1, t_vec3 v2, t_point p)
{
	t_vec3	normal_vector;
	t_plain	pl;

	normal_vector = vector_cross_product(v1, v2);
	pl.a = normal_vector.x;
	pl.b = normal_vector.y;
	pl.c = normal_vector.z;
	pl.d = - (pl.a * p.x + pl.b * p.y + pl.c * p.z);
	return (pl);
}

t_plain plain_from_1_vector(t_vec3 normal_vector, t_point p)
{
	t_plain	pl;

	pl.a = normal_vector.x;
	pl.b = normal_vector.y;
	pl.c = normal_vector.z;
	pl.d = - (pl.a * p.x + pl.b * p.y + pl.c * p.z);
	return (pl);
}
