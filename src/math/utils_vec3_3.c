/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:40:26 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/25 20:26:07 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	create_vec3_color_arr(int *arr)
{
	t_vec3	res;

	res.x = (double)arr[0] / 255.0;
	res.y = (double)arr[1] / 255.0;
	res.z = (double)arr[2] / 255.0;
	return (res);
}

t_vec3	multiply_vec3(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x * vec2.x;
	res.y = vec1.y * vec2.y;
	res.z = vec1.z * vec2.z;
	return (res);
}

t_vec3	shrink_vec3(t_vec3 vec, double min, double max)
{
	t_vec3	res;

	res.x = min_double(max, max_double(vec.x, min));
	res.y = min_double(max, max_double(vec.y, min));
	res.z = min_double(max, max_double(vec.z, min));
	return (res);
}
