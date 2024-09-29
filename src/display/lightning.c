/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:56 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 16:11:33 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	is_in_shadow(t_data *data, t_hit *hit, t_vec3 *light_dir, double dist)
{
	t_ray	ray;
	t_hit	new_hit;

	ray.ray_direction = *light_dir;
	ray.ray_origin = add(hit->world_position, scale(*light_dir, 0.00001));
	ray_trace(data, &ray, &new_hit);
	if (new_hit.found == 1 && new_hit.hit_distance < dist)
	{
		return (1);
	}
	return (0);
}

t_vec3	calculate_light(t_data *data, t_ray *ray, t_hit *hit)
{
	t_vec3  effective_color = multiply_vec3(hit->color, scale(data->light.vec3_color, data->light.ratio));
	t_vec3  ambitient = scale(multiply_vec3(hit->color, data->ambitient_light.vec3_color), data->ambitient_light.ratio);

	(void)ray;
	double dist;
	t_vec3	light_dir;
	t_vec3	difuse = create_vec3(0, 0, 0);
	t_vec3	specular = create_vec3(0, 0, 0);
	light_dir = subtract(data->light.vec3_cords, hit->world_position);
	dist = sqrt(dot_product(light_dir, light_dir));
	light_dir = normalize(light_dir);
	double light_dot = dot_product(light_dir, hit->world_normal);
	if (light_dot > 0 && !is_in_shadow(data, hit, &light_dir, dist))
	{
		difuse = scale(effective_color, light_dot);
		t_vec3	reflect = vec_reflect_norm(scale(light_dir, -1.0), hit->world_normal);
		double reflect_dot = dot_product(reflect, ray->ray_direction);
		if (reflect_dot > 0)
		{
			double factor = pow(reflect_dot, 10);
			specular = scale(data->light.vec3_color, data->light.ratio * factor); 
		}
	}
	return (add(add(ambitient, difuse), specular));
}