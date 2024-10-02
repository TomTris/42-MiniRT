/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cylinders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:57:34 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 22:50:29 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_type_distance_cy(t_hit *hit, double distance)
{
	hit->hit_distance = distance;
	hit->found = 1;
	hit->type = 3;
	hit->type_cy = 1;
}

typedef struct s_val_holder
{
	t_vec3	cap_center;
	double	t_cap;
	t_vec3	inter_p;
	t_vec3	dist_to_center;
}	t_val_holder;

void	top_circle(t_data *data, t_ray *ray, t_hit *hit, int i)
{
	t_val_holder	t;

	t.cap_center = add(data->cylinders[i].vec3_cords, \
	scale(data->cylinders[i].vec3_norm, data->cylinders[i].height / 2.0));
	t.t_cap = dot_product(subtract(t.cap_center, ray->ray_origin), \
	data->cylinders[i].vec3_norm) / dot_product(ray->ray_direction, \
	data->cylinders[i].vec3_norm);
	if (t.t_cap > 0 && t.t_cap < hit->hit_distance)
	{
		t.inter_p = add(ray->ray_origin, scale(ray->ray_direction, t.t_cap));
		t.dist_to_center = subtract(t.inter_p, t.cap_center);
		if (dot_product(t.dist_to_center, t.dist_to_center) <= \
		(data->cylinders[i].diameter / 2.0) * \
		(data->cylinders[i].diameter / 2.0))
		{
			set_type_distance_cy(hit, t.t_cap);
			hit->color = data->cylinders[i].vec3_color;
			hit->cords = t.inter_p;
			hit->normal = data->cylinders[i].vec3_norm;
			hit->type_cy = 3;
			hit->cylinder = &data->cylinders[i];
		}
	}
}

void	bottom_circle(t_data *data, t_ray *ray, t_hit *hit, int i)
{
	t_val_holder	t;

	t.cap_center = subtract(data->cylinders[i].vec3_cords, \
	scale(data->cylinders[i].vec3_norm, data->cylinders[i].height / 2.0));
	t.t_cap = dot_product(subtract(t.cap_center, ray->ray_origin), \
	data->cylinders[i].vec3_norm) / dot_product(ray->ray_direction, \
	data->cylinders[i].vec3_norm);
	if (t.t_cap > 0 && t.t_cap < hit->hit_distance)
	{
		t.inter_p = add(ray->ray_origin, scale(ray->ray_direction, t.t_cap));
		t.dist_to_center = subtract(t.inter_p, t.cap_center);
		if (dot_product(t.dist_to_center, t.dist_to_center) <= \
		(data->cylinders[i].diameter / 2.0) * \
		(data->cylinders[i].diameter / 2.0))
		{
			set_type_distance_cy(hit, t.t_cap);
			hit->color = data->cylinders[i].vec3_color;
			hit->cords = t.inter_p;
			hit->normal = scale(data->cylinders[i].vec3_norm, 1.0);
			hit->type_cy = 2;
			hit->cylinder = &data->cylinders[i];
		}
	}
}

void	intersection_height(t_data *data, t_ray *ray, t_hit *hit, int i)
{
	if (hit->vars_sp.descriminent >= 0)
	{
		hit->vars_sp.t = (-hit->vars_sp.b - sqrt(hit->vars_sp.descriminent)) \
		/ (2.0 * hit->vars_sp.a);
		if (hit->vars_sp.t > 0 && hit->vars_sp.t < hit->hit_distance)
		{
			hit->vars_sp.d = dot_product(subtract(add(ray->ray_origin, \
scale(ray->ray_direction, hit->vars_sp.t)), \
subtract(data->cylinders[i].vec3_cords, scale(data->cylinders[i].vec3_norm, \
data->cylinders[i].height / 2.0))), data->cylinders[i].vec3_norm);
			if (hit->vars_sp.d >= 0 && hit->vars_sp.d <= \
			data->cylinders[i].height)
			{
				set_type_distance_cy(hit, hit->vars_sp.t);
				hit->color = data->cylinders[i].vec3_color;
				hit->cords = add(data->cylinders[i].vec3_cords, \
				scale(data->cylinders[i].vec3_norm, hit->vars_sp.d - \
				data->cylinders[i].height / 2.0));
				hit->normal = \
				normalize(subtract(hit->cords, data->cylinders[i].vec3_cords));
			}
		}
	}
}

// | (Q - P) - (((Q - P) * n) * n) | = r * r
void	handle_cylinders(t_data *data, t_ray *ray, t_hit *hit)
{
	int		i;
	t_vec3	temp;
	t_vec3	temp2;

	i = 0;
	while (i < data->amount_of_cylinders)
	{
		temp = subtract(ray->ray_direction, scale(data->cylinders[i].vec3_norm, \
		dot_product(ray->ray_direction, data->cylinders[i].vec3_norm)));
		temp2 = subtract(subtract(ray->ray_origin, \
data->cylinders[i].vec3_cords), scale(data->cylinders[i].vec3_norm, \
dot_product(subtract(ray->ray_origin, data->cylinders[i].vec3_cords), \
data->cylinders[i].vec3_norm)));
		hit->vars_sp.a = dot_product(temp, temp);
		hit->vars_sp.b = 2 * dot_product(temp2, temp);
		hit->vars_sp.c = dot_product(temp2, temp2) - \
		data->cylinders[i].diameter * data->cylinders[i].diameter / 4.0;
		hit->vars_sp.descriminent = hit->vars_sp.b * hit->vars_sp.b - \
		4 * hit->vars_sp.a * hit->vars_sp.c;
		intersection_height(data, ray, hit, i);
		top_circle(data, ray, hit, i);
		bottom_circle(data, ray, hit, i);
		i++;
	}
}
