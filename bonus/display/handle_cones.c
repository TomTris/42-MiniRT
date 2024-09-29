/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cones.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:10:33 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 21:22:27 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_point	from_vec3_to_tpoint(t_vec3 vec)
{
	t_point	p;

	p.x = vec.x;
	p.y = vec.y;
	p.z = vec.z;
	return (p);
}

t_cone_tom	from_cone_to_cone_tom(t_cone *cone)
{
	t_cone_tom	ret;

	ret.pA = from_vec3_to_tpoint(cone->vec3_cords);
	ret.r = cone->diameter / 2.0;
	ret.vAO = cone->vec3_norm;
	ret.pO = from_vec3_to_tpoint(add(cone->vec3_cords, \
		scale(cone->vec3_norm, cone->height)));
	return (ret);
}

void	handle_cones(t_data *data, t_ray *ray, t_hit *hit)
{
	int 		i;
	t_line		line;
	t_cone_tom	cone;
	t_point_x_nor_vec res;

	i = 0;
	while (i < data->amount_of_cones)
	{

		line.p = from_vec3_to_tpoint(ray->ray_origin);
		line.dv = ray->ray_direction;
		cone = from_cone_to_cone_tom(&(data->cones[i]));
		res = line_x_cone(&line, &cone);
		if (res.amount == 1)
		{
			if (hit->hit_distance > res.t)
			{
				hit->found = 1;
				hit->type = 4;
				hit->hit_distance = res.t;
				hit->color = data->cones[i].vec3_color;
				hit->world_normal = res.v;
				hit->world_position = add(ray->ray_origin, scale(ray->ray_direction, res.t));
			}
		}
		i++;
	}
	// printf("--%f--\n", hit->hit_distance);
}
