/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cones.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:10:33 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/01 18:48:37 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	handle_cones(t_data *data, t_ray *ray, t_hit *hit)
{
	int 		i;
	t_line		line;
	t_point_x_nor_vec res;

	i = 0;
	while (i < data->amount_of_cones)
	{
		line.p = ray->ray_origin;
		line.dv = ray->ray_direction;
		res = line_x_cone(&line, &(data->cones[i]));
		if (res.amount == 1)
		{
			if (hit->hit_distance > res.t)
			{
				hit->found = 1;
				hit->type = 4;
				hit->hit_distance = res.t;
				hit->color = res.color;
				hit->world_normal = res.v;
				hit->world_position = res.p;
				hit->cone = &data->cones[i];
				hit->texture = data->cones[i].texture;
			}
		}
		i++;
	}
}
