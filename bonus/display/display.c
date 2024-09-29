/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 17:09:31 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	transform_to_channel(double v)
{
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	return ((int)(v * 255.0));
}

uint32_t	get_color_from_vec3(t_vec3 vec)
{
	uint32_t	res;

	res = transform_to_channel(vec.x) << 24
		| transform_to_channel(vec.y) << 16
		| transform_to_channel(vec.z) << 8 | 255;
	return (res);
}

void	closest_hit2(t_data *data, t_ray *ray, t_hit *hit)
{
	(void)data;
	if (hit->type == 3)
	{
		hit->world_position = add(ray->ray_origin, \
			scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(subtract(hit->world_position, \
			add(hit->cords, scale(hit->normal, \
			dot_product(subtract(hit->world_position, hit->cords), \
			hit->normal)))));
	}
	else if (hit->type == 4)
	{
		hit->world_position = add(ray->ray_origin,
				scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(subtract(\
			subtract(hit->world_position, hit->cords), \
			scale(hit->normal, dot_product(\
			subtract(hit->world_position, hit->cords), hit->normal))));
	}
}

void	closest_hit(t_data *data, t_ray *ray, t_hit *hit)
{
	t_vec3	origin;

	(void)data;
	if (hit->type == 1)
	{
		origin = \
		subtract(ray->ray_origin, hit->cords);
		hit->world_position = add(origin,
				scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(hit->world_position);
		hit->world_position = \
		add(hit->world_position, hit->cords);
	}
	else if (hit->type == 2)
	{
		hit->world_position = add(ray->ray_origin,
				scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = hit->normal;
	}
	else
		closest_hit2(data, ray, hit);
}

void	ray_trace(t_data *data, t_ray *ray, t_hit *hit)
{
	hit->found = 0;
	hit->hit_distance = MAXFLOAT;
	handle_spheres(data, ray, hit);
	handle_planes(data, ray, hit);
	handle_cylinders(data, ray, hit);
	handle_cones(data, ray, hit);
	closest_hit(data, ray, hit);
}
