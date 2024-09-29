/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.create_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:06:42 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 00:28:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

//create a line from a valid vector and a point
t_line line_from_vector_and_point(t_vec3 vec, t_point p)
{
	t_line line;

	line.direction_vector.x = 0;
	line.direction_vector.y = 0;
	line.direction_vector.z = 0;
	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		return (perror("Invalid Vector"), line);
	line.direction_vector = vec;
	line.point = p;
	return (line);
}
