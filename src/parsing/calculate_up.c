/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:43:40 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/21 20:53:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// void	calculate_up(t_data *data)
// {
// 	t_vec3		vec_up;
// 	t_vec3		rotation_axis;
// 	t_matrix3	rotation_matrix;
// 	t_vec3		res;


// 	data->camera.vec3 = normalize(data->camera.vec3);
// 	vec_up = create_vec3(0, 1, 0);
// 	if (are_vectors_similar(data->camera.vec3, vec_up))
// 	{
// 		vec_up = create_vec3(1, 0, 0);
// 	}
// 	rotation_axis = cross(data->camera.vec3, vec_up);
// 	rotation_axis = normalize(rotation_axis);
// 	rotation_matrix = create_matrix(rotation_axis, M_PI / 2.0);
// 	res = apply_matrix(data->camera.vec3, &rotation_matrix);
// 	if (res.y < 0.0)
// 		res = scale(res, -1.0);
// 	// t_vec3 temp = create_vec3(1, 0, 1);
// 	// t_vec3 right = cross(temp, data->camera.vec3);
// 	// temp = cross(data->camera.vec3, right);
// 	// dprintf(1, "%f  %f  %f\n", res.x, res.y, res.z);
// 	// dprintf(1, "%f  %f  %f\n", temp.x, temp.y, temp.z);
// 	data->camera.world_up = res;
// }


void	calculate_up(t_data *data)
{
	double x;
	double y;
	double z;
	double x2;
	double y2;
	
	x = data->camera.vec3.x;
	y = data->camera.vec3.y;
	z = data->camera.vec3.z;

	if (x == 0 && y == 0)
	{
		data->camera.world_up.x = 0;
		data->camera.world_up.y = 1;
		data->camera.world_up.z = 0;
		return ;
	}

	data->camera.world_up.z = sqrt(x * z + y * y);
	x2 = sqrt(z * z - ((z * z * y * y) / (x * x + y * y)));
	y2 = z * y / sqrt(x * x + y * y);
	if (z > 0)
	{
		if ((x > 0) && (x2 > 0))
			x2 *= -1;
		if ((y > 0) && (y2 > 0))
			y2 *= -1;
		data->camera.world_up.x = x2;
		data->camera.world_up.y = y2;
	}
	else
	{
		if (((x > 0) && (x2 < 0)) || ((x < 0) && (x2 > 0)))
			x2 *= -1;
		if (((y > 0) && (y2 < 0)) || ((y < 0) && (y2 > 0)))
			y2 *= -1;
		data->camera.world_up.x = x2;
		data->camera.world_up.y = y2;
	}
}
