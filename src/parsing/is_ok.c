/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 13:51:45 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	check_is_vector_ok(double *vector)
{
	double	len_vec;

	len_vec = get_len_vector(vector);
	if (len_vec - TOLARANCE > 1.0 || len_vec + TOLARANCE < 1.0)
		return (0);
	return (1);
}

int	check_all_vectors(t_data *data)
{
	int	i;

	i = 0;
	if (!check_is_vector_ok(data->camera.vector))
		return (display_error_message("Camera Vector not OK"), 0);
	while (i < data->amount_of_cones)
	{
		if (!check_is_vector_ok(data->cones[i].vector))
			return (display_error_message("Cone vector not OK"), 0);
		i++;
	}
	i = 0;
	while (i < data->amount_of_cylinders)
	{
		if (!check_is_vector_ok(data->cylinders[i].vector))
			return (display_error_message("Cylinder vector not OK"), 0);
		i++;
	}
	i = 0;
	while (i < data->amount_of_planes)
		if (!check_is_vector_ok(data->planes[i++].vector))
			return (display_error_message("Plane vector not OK"), 0);
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
	if (!check_all_vectors(data))
		return (0);
	return (1);
}
