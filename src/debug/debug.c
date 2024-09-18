/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:00:23 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 16:54:12 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	output_data(t_data	*data)
{
	dprintf(1, "A %f %d,%d,%d\n", data->ambitient_light.ratio, data->ambitient_light.colors[0], data->ambitient_light.colors[1], data->ambitient_light.colors[2]);
	dprintf(1, "C %f,%f,%f  %f,%f,%f  %d\n", data->camera.cords[0], data->camera.cords[1], data->camera.cords[2], data->camera.vector[0], data->camera.vector[1], data->camera.vector[2], data->camera.fov);
	dprintf(1, "L %f,%f,%f  %f, %d,%d,%d\n", data->light.cords[0], data->light.cords[1], data->light.cords[2], data->light.ratio, data->light.colors[0], data->light.colors[1], data->light.colors[2]);
	for (int i = 0; i < data->amount_of_spheres; i++)
	{
		t_sphere sphere =  data->spheres[i];
		dprintf(1, "sp %f,%f,%f   %f  %d,%d,%d\n", sphere.cords[0], sphere.cords[1], sphere.cords[2], sphere.diameter, sphere.colors[0], sphere.colors[1], sphere.colors[2]);
	}
	for (int i = 0; i < data->amount_of_planes; i++)
	{
		t_plane plane =  data->planes[i];
		dprintf(1, "pl %f,%f,%f   %f,%f,%f  %d,%d,%d\n", plane.cords[0], plane.cords[1], plane.cords[2], plane.vector[0], plane.vector[1], plane.vector[2], plane.colors[0], plane.colors[1], plane.colors[2]);
	}
	for (int i = 0; i < data->amount_of_cylinders; i++)
	{
		t_cylinder cylinder = data->cylinders[i];
		dprintf(1, "cy %f,%f,%f   %f,%f,%f  %f %f  %d,%d,%d\n", cylinder.cords[0], cylinder.cords[1], cylinder.cords[2], cylinder.vector[0], cylinder.vector[1], cylinder.vector[2], cylinder.diameter, cylinder.height, cylinder.colors[0], cylinder.colors[1], cylinder.colors[2]);
	}
	for (int i = 0; i < data->amount_of_cones; i++)
	{
		t_cone cone = data->cones[i];
		dprintf(1, "co %f,%f,%f   %f,%f,%f  %f %f  %d,%d,%d\n", cone.cords[0], cone.cords[1], cone.cords[2], cone.vector[0], cone.vector[1], cone.vector[2], cone.diameter, cone.height, cone.colors[0], cone.colors[1], cone.colors[2]);
	}
}