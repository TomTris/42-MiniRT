/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:12:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 18:58:10 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	dot_product(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	normalize(t_vec3 vec)
{
	double	len;
	t_vec3	res;

	len = sqrt(dot_product(vec, vec));
	res.x = vec.x / len;
	res.y = vec.y / len;
	res.z = vec.z / len;
	return (res);
}

t_vec3	scale(t_vec3 vec, double scale)
{
	t_vec3	res;

	res.x = vec.x * scale;
	res.y = vec.y * scale;
	res.z = vec.z * scale;
	return (res);
}

t_vec3	add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

// x x
// y y
// z z


t_vec3	cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (result);
}
