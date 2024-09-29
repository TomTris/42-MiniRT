/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:43:40 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 21:57:10 by qdo              ###   ########.fr       */
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

typedef struct s_vars
{
	double	x;
	double	z;
	double	y;
	double	x2;
	double	z2;
}	t_5vars;

void	calculate_up2(t_5vars vars, t_data *data)
{
	data->camera.world_up.y = sqrt(vars.x * vars.x + vars.z * vars.z);
	vars.x2 = sqrt(vars.y * vars.y - \
		((vars.y * vars.y * vars.z * vars.z) / \
		(vars.x * vars.x + vars.z * vars.z)));
	vars.z2 = vars.y * vars.z / sqrt(vars.x * vars.x + vars.z * vars.z);
	if (vars.y > 0)
	{
		if ((vars.x > 0) && (vars.x2 > 0))
			vars.x2 *= -1;
		if ((vars.z > 0) && (vars.z2 > 0))
			vars.z2 *= -1;
	}
	else
	{
		if (((vars.x > 0) && (vars.x2 < 0)) || ((vars.x < 0) && (vars.x2 > 0)))
			vars.x2 *= -1;
		if (((vars.z > 0) && (vars.z2 < 0)) || ((vars.z < 0) && (vars.z2 > 0)))
			vars.z2 *= -1;
	}
	data->camera.world_up.x = vars.x2;
	data->camera.world_up.z = vars.z2;
}

void	calculate_up(t_data *data)
{
	t_5vars	vars;

	vars.x = data->camera.vec3.x;
	vars.y = data->camera.vec3.y;
	vars.z = data->camera.vec3.z;
	if (vars.x == 0 && vars.z == 0)
	{
		data->camera.world_up.x = 0;
		data->camera.world_up.z = 1;
		data->camera.world_up.y = 0;
		return ;
	}
	calculate_up2(vars, data);
}
