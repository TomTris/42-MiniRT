/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cones.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:10:33 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/30 20:59:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	handle_cones(t_data *data, t_ray *ray, t_hit *hit)
{
	int 		i;
	t_line		line;
	t_point_x_nor_vec res;
	static int	a = 0;
	a++;
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
				hit->color = create_vec3(1, 1, 1);
				if (a % 2 || a % 3)
					hit->color = data->cones[i].vec3_color;
				hit->world_normal = res.v;
				hit->world_position = add(ray->ray_origin, scale(ray->ray_direction, res.t));
			}
		}
		i++;
	}
}
