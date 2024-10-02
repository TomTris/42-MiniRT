/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:20:36 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 18:20:15 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

double	angle_between_vec(t_vec3 vec1, t_vec3 vec2)
{
	double	cos_theta;

	cos_theta = dot_product(normalize(vec1), normalize(vec2));
	cos_theta = fmax(-1.0, fmin(1.0, cos_theta));
	return (acos(cos_theta));
}

int	are_vectors_similar(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (1);
	return (0);
}

t_vec3	create_vec3_arr(double *vec)
{
	t_vec3	res;

	res.x = vec[0];
	res.y = vec[1];
	res.z = vec[2];
	return (res);
}

t_vec3	subtract(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}
