/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.pre_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:15:44 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 22:53:28 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

int	is_valid_vector(t_vec3 vec)
{
	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		return (0);
	return (1);
}

int	is_valid_line(t_line line)
{
	return (is_valid_vector(line.direction_vector));
}

int	is_valid_plain(t_plain plain)
{
	if (plain.a == 0 && plain.b == 0 && plain.c == 0)
		return (0);
	return (1);
}

int	is_vector_plain_parallel(t_vec3 vec, t_plain pl)
{
	if (vec.x * pl.a + vec.y * pl.b + + vec.z * pl.c == 0)
		return (1);
	return (0);
}

int are_3_points(t_point point1, t_point point2, t_point point3)
{
	if (point1.x == point2.x && point1.y == point2.y && point1.z == point2.z)
		return (0);
	if (point1.x == point3.x && point1.y == point3.y && point1.z == point3.z)
		return (0);
	if (point3.x == point2.x && point3.y == point2.y && point3.z == point2.z)
		return (0);
	return (1);
}
