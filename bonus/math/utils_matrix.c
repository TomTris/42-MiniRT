/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:28:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_matrix3	create_matrix(t_vec3 axis, double angle)
{
	t_matrix3	matrix;
	double		sin_a;
	double		cos_a;
	double		one_minus_cos_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	one_minus_cos_a = 1.0 - cos_a;
	axis = normalize(axis);
	matrix.m[0][0] = cos_a + axis.x * axis.x * one_minus_cos_a;
	matrix.m[0][1] = axis.x * axis.y * one_minus_cos_a - axis.z * sin_a;
	matrix.m[0][2] = axis.x * axis.z * one_minus_cos_a + axis.y * sin_a;
	matrix.m[1][0] = axis.y * axis.x * one_minus_cos_a + axis.z * sin_a;
	matrix.m[1][1] = cos_a + axis.y * axis.y * one_minus_cos_a;
	matrix.m[1][2] = axis.y * axis.z * one_minus_cos_a - axis.x * sin_a;
	matrix.m[2][0] = axis.z * axis.x * one_minus_cos_a - axis.y * sin_a;
	matrix.m[2][1] = axis.z * axis.y * one_minus_cos_a + axis.x * sin_a;
	matrix.m[2][2] = cos_a + axis.z * axis.z * one_minus_cos_a;
	return (matrix);
}

t_vec3	apply_matrix(t_vec3 vec, t_matrix3 *matrix)
{
	t_vec3	result;

	result.x = \
	matrix->m[0][0] * vec.x + matrix->m[0][1] * vec.y + matrix->m[0][2] * vec.z;
	result.y = \
	matrix->m[1][0] * vec.x + matrix->m[1][1] * vec.y + matrix->m[1][2] * vec.z;
	result.z = \
	matrix->m[2][0] * vec.x + matrix->m[2][1] * vec.y + matrix->m[2][2] * vec.z;
	return (result);
}
