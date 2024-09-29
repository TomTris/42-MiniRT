/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:29:40 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/21 20:19:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	get_direction_ray(t_data *data, double offset_x, double offset_y)
{
	t_vec3	cam_right;
	double	half_width;
	double	half_height;
	double	ratio;
	t_vec3	res;

	cam_right = cross(data->camera.vec3, data->camera.world_up);
	cam_right = normalize(cam_right);
	ratio = (double)data->mlx->width / (double)data->mlx->height;
	half_height = tan(data->camera.fov / 2.0);
	half_width = ratio * half_height;
	offset_x *= half_width;
	offset_y *= half_height;
	res = add(data->camera.vec3, add(scale(cam_right, offset_x), \
	scale(data->camera.world_up, offset_y)));
	res = normalize(res);
	return (res);
}
