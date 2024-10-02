/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cones.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:10:33 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	setter_cones(t_data *data, t_hit *hit, int i, t_point_x_nor_vec *res)
{
	hit->found = 1;
	hit->type = 4;
	hit->hit_distance = res->t;
	hit->color = res->color;
	hit->world_normal = res->v;
	hit->world_position = res->p;
	hit->cone = &data->cones[i];
	hit->texture = data->cones[i].texture;
}

void	handle_cones(t_data *data, t_ray *ray, t_hit *hit)
{
	int					i;
	t_line				line;
	t_point_x_nor_vec	res;

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
				setter_cones(data, hit, i, &res);
			}
		}
		i++;
	}
}
