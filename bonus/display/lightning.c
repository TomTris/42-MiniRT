/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:56 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 16:34:50 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	random_vector(void)
{
	t_vec3	res;

	res.x = ((double)rand() / (double)RAND_MAX - 0.5) * 2.0;
	res.y = ((double)rand() / (double)RAND_MAX - 0.5) * 2.0;
	res.z = ((double)rand() / (double)RAND_MAX - 0.5) * 2.0;
	return (normalize(res));
}

int	is_in_shadow(t_data *data, t_hit *hit, t_vec3 *light_dir, double dist)
{
	t_ray	ray;
	t_hit	new_hit;


	ray.ray_direction = *light_dir;
	ray.ray_origin = add(hit->world_position, scale(hit->world_normal, 0.00001));
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
	double				factor;
	double				dist;
	int					i;
	t_vec3				final;
	t_vec3				color;
}	t_calculate_light;




void	loop_calculate_light(t_data *data, t_ray *ray, t_hit *hit, \
t_calculate_light *cl)
{
	cl->effective_color = multiply_vec3(cl->color, \
	scale(data->light[cl->i].vec3_color, data->light[cl->i].ratio));
	cl->difuse = create_vec3(0, 0, 0);
	cl->specular = create_vec3(0, 0, 0);
	cl->light_dir = subtract(data->light[cl->i].vec3_cords, hit->world_position);
	cl->dist = sqrt(dot_product(cl->light_dir, cl->light_dir));
	cl->light_dir = normalize(cl->light_dir);
	cl->light_dot = dot_product(cl->light_dir, hit->world_normal);
	if (cl->light_dot > 0 && !is_in_shadow(data, hit, &cl->light_dir, cl->dist))
	{
		cl->difuse = scale(cl->effective_color, cl->light_dot);
		cl->reflect = vec_reflect_norm(scale(cl->light_dir, -1.0), \
			hit->world_normal);
		cl->reflect_dot = dot_product(cl->reflect, ray->ray_direction);
		if (cl->reflect_dot > 0)
		{
			cl->factor = pow(cl->reflect_dot, 50);
			cl->specular = scale(data->light[cl->i].vec3_color, \
				data->light[cl->i].ratio * cl->factor);
		}
	}
}

t_vec3	calculate_light(t_data *data, t_ray *ray, t_hit *hit)
{
	t_calculate_light	cl;

	cl.color = get_color(hit);
	cl.ambitient = scale(multiply_vec3(cl.color, \
		data->ambitient_light.vec3_color), data->ambitient_light.ratio);
	cl.final = create_vec3(0, 0, 0);
	cl.i = 0;
	while (cl.i < data->amount_of_lights)
	{
		loop_calculate_light(data, ray, hit, &cl);
		cl.final = add(cl.final, add(cl.difuse, cl.specular));
		cl.i++;
	}
	return (add(cl.final, cl.ambitient));
}
