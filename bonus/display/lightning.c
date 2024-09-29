/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:56 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 18:13:37 by obrittne         ###   ########.fr       */
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

typedef struct s_calculate_light
{
	t_vec3	effective_color;
	t_vec3	ambitient;
	t_vec3	light_dir;
	t_vec3	difuse;
	t_vec3	specular;
	double	light_dot;
	t_vec3	reflect;
	double	reflect_dot;
	double	factor;
}	t_calculate_light;

void	calculate_light2(t_data *data, t_ray *ray, t_hit *hit,
		t_calculate_light *cl)
{
	cl->difuse = scale(cl->effective_color, cl->light_dot);
	cl->reflect = vec_reflect_norm(scale(cl->light_dir, -1.0), \
		hit->world_normal);
	cl->reflect_dot = dot_product(cl->reflect, ray->ray_direction);
	if (cl->reflect_dot > 0)
	{
		cl->factor = pow(cl->reflect_dot, 10);
		cl->specular = scale(data->light.vec3_color, \
			data->light.ratio * cl->factor);
	}
}

t_vec3	calculate_light(t_data *data, t_ray *ray, t_hit *hit)
{
	double				dist;
	t_calculate_light	cl;

	(void)ray;
	cl.effective_color = multiply_vec3(hit->color, \
		scale(data->light.vec3_color, data->light.ratio));
	cl.ambitient = scale(multiply_vec3(hit->color, \
		data->ambitient_light.vec3_color), data->ambitient_light.ratio);
	cl.difuse = create_vec3(0, 0, 0);
	cl.specular = create_vec3(0, 0, 0);
	cl.light_dir = subtract(data->light.vec3_cords, hit->world_position);
	dist = sqrt(dot_product(cl.light_dir, cl.light_dir));
	cl.light_dir = normalize(cl.light_dir);
	cl.light_dot = dot_product(cl.light_dir, hit->world_normal);
	if (cl.light_dot > 0 && !is_in_shadow(data, hit, &cl.light_dir, dist))
	{
		calculate_light2(data, ray, hit, &cl);
	}
	return (add(add(cl.ambitient, cl.difuse), cl.specular));
}
