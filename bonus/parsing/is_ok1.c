/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:53:08 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

double	get_distance(t_vec3 *norm, t_vec3 *point, t_vec3 *camera)
{
	t_var_sphere	vars;

	vars.d = dot_product(subtract(*camera, *point), *norm);
	return (fabs(vars.d));
}

int	check_planes(t_data *data, int i)
{
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
		data->planes[i].vec3_norm = scale(data->planes[i].vec3_norm, \
get_factor(&data->planes[i].vec3_norm, \
&data->planes[i].vec3_cords, &data->camera.vec3_cords));
		data->planes[i].dist = get_distance(&data->planes[i].vec3_norm, \
		&data->planes[i].vec3_cords, &data->camera.vec3_cords);
		i++;
	}
	return (1);
}
