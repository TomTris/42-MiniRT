/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 14:56:21 by obrittne         ###   ########.fr       */
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

int	check_half(t_data *data, int i)
{
	while (i < data->amount_of_spheres)
	{
		data->spheres[i].vec3_cords = create_vec3_arr(data->spheres[i].cords);
		data->spheres[i].vec3_color = \
		create_vec3_color_arr(data->spheres[i].colors);
		i++;
	}
	i = 0;
	while (i < data->amount_of_planes)
	{
		if (!check_is_vector_ok(data->planes[i].vector))
			return (display_error_message("Plane vector not OK"), 0);
		data->planes[i].vec3_color = \
		create_vec3_color_arr(data->planes[i].colors);
		data->planes[i].vec3_cords = \
		create_vec3_arr(data->planes[i].cords);
		data->planes[i].vec3_norm = \
		normalize(create_vec3_arr(data->planes[i].vector));
		i++;
	}
	return (1);
}

int	check_all_vectors(t_data *data, int i)
{
	if (!check_is_vector_ok(data->camera.vector))
		return (display_error_message("Camera Vector not OK"), 0);
	data->camera.vec3 = create_vec3_arr(data->camera.vector);
	data->light.vec3_color = create_vec3_color_arr(data->light.colors);
	data->light.vec3_cords = create_vec3_arr(data->light.cords);
	data->ambitient_light.vec3_color = \
	create_vec3_color_arr(data->ambitient_light.colors);
	if (!check_half(data, 0))
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
	return (1);
}

int	check_if_ok(t_data *data)
{
	if (!data->seen_ambitient_light)
		return (display_error_message("Ambitient light is missing"), 0);
	if (!data->seen_camera)
		return (display_error_message("Camera is missing"), 0);
	if (!data->seen_light)
		return (display_error_message("Light is missing"), 0);
	if (!check_all_vectors(data, 0))
		return (0);
	calculate_up(data);
	return (1);
}
