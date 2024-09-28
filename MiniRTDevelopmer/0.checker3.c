/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.checker3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:58:23 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 20:54:15 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

int is_on_plain(t_plain pl, t_point p)
{
	if (pl.a * p.x + pl.b * p.y + pl.c + p.z + pl.d == 0)
		return (1);
	return (0);
}

int	is_valid_cone(t_cone cone)
{
	t_vec3	vAO;

	vAO = vector_AO_form_A_O(cone.pA, cone.pO);
	if (is_valid_vector(cone.vAO) && is_valid_vector(vAO) && cone.r > 0 \
		&& is_two_vector_same_direction(cone.vAO, vAO))
		return (1);
	return (0);
}

int	is_perpenticular(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z == 0)
		return (1);
	return (0);
}

//nor parralel / in -> 0
//in -> 1
//parallel -> 2
int	is_line_parallel_or_in_plain(t_line line, t_plain pl)
{
	t_vec3	normal_vector;

	normal_vector.x = pl.a;
	normal_vector.y = pl.b;
	normal_vector.z = pl.c;
	if (is_perpenticular(line.direction_vector, normal_vector))
	{
		if (is_on_plain(pl, line.point) == 1)
			return (1);
		return (2);
	}
	return (0);
}

int	are_vectors_parallel(t_line line, t_plain pl)
{
	t_vec3	normal_vector;

	normal_vector.x = pl.a;
	normal_vector.y = pl.b;
	normal_vector.z = pl.c;
	if (is_perpenticular(line.direction_vector, normal_vector))
	{
		if (is_on_plain(pl, line.point) == 1)
			return (1);
		return (2);
	}
	return (0);
}
