/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/01 19:53:58 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	check_is_vector_ok(double *vector)
{
	double	len_vec;

	len_vec = get_len_vector_d(vector);
	if (len_vec - TOLARANCE > 1.0 || len_vec + TOLARANCE < 1.0)
		return (0);
	return (1);
}

int	check_spheres(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount_of_spheres)
	{
		data->spheres[i].vec3_cords = create_vec3_arr(data->spheres[i].cords);
		data->spheres[i].vec3_color = \
		create_vec3_color_arr(data->spheres[i].colors);
		i++;
	}
	return (1);
}

int	check_cones(t_data *data, int i)
{
	while (i < data->amount_of_cones)
	{
		if (!check_is_vector_ok(data->cones[i].vector))
			return (display_error_message("Cone vector not OK"), 0);
		data->cones[i].vec3_cords = \
		create_vec3_arr(data->cones[i].cords);
		data->cones[i].vec3_color = \
		create_vec3_color_arr(data->cones[i].colors);
		data->cones[i].vec3_norm = \
		normalize(create_vec3_arr(data->cones[i].vector));
		calculate_cone(&data->cones[i]);
		i++;
	}
	i = 0;
	while (i < data->amount_of_lights)
	{
		data->light[i].vec3_color = \
		create_vec3_color_arr(data->light[i].colors);
		data->light[i].vec3_cords = create_vec3_arr(data->light[i].cords);
		i++;
	}
	return (check_spheres(data));
}

int	check_all_vectors(t_data *data, int i)
{
	if (!check_is_vector_ok(data->camera.vector))
		return (display_error_message("Camera Vector not OK"), 0);
	data->camera.vec3 = create_vec3_arr(data->camera.vector);
	data->camera.vec3_cords = create_vec3_arr(data->camera.cords);
	data->ambitient_light.vec3_color = \
	create_vec3_color_arr(data->ambitient_light.colors);
	if (!check_planes(data, 0))
		return (0);
	while (i < data->amount_of_cylinders)
	{
		if (!check_is_vector_ok(data->cylinders[i].vector))
			return (display_error_message("Cylinder vector not OK"), 0);
		data->cylinders[i].vec3_cords = \
		create_vec3_arr(data->cylinders[i].cords);
		data->cylinders[i].vec3_color = \
		create_vec3_color_arr(data->cylinders[i].colors);
		data->cylinders[i].vec3_norm = \
		normalize(create_vec3_arr(data->cylinders[i].vector));
		i++;
	}
	return (check_cones(data, 0));
}

int	check_if_ok(t_data *data)
{
	if (!data->seen_ambitient_light)
		return (display_error_message("Ambitient light is missing"), 0);
	if (!data->seen_camera)
		return (display_error_message("Camera is missing"), 0);
	if (data->amount_of_lights == 0)
		return (display_error_message("Light is missing"), 0);
	if (!check_all_vectors(data, 0))
		return (0);
	calculate_up(data);
	return (1);
}
