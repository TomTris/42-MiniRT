/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spheres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:29:07 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

static void	setter(t_hit *hit, t_data *data, int i)
{
	hit->type = 1;
	hit->found = 1;
	hit->hit_distance = hit->vars_sp.t;
	hit->color = data->spheres[i].vec3_color;
	hit->cords = data->spheres[i].vec3_cords;
	hit->sphere = &data->spheres[i];
	hit->checkers = data->spheres[i].checkers;
	hit->texture = data->spheres[i].texture;
}

void	handle_spheres(t_data *data, t_ray *ray, t_hit *hit)
{
	int		i;
	t_vec3	origin;

	i = -1;
	while (++i < data->amount_of_spheres)
	{
		origin = subtract(ray->ray_origin, data->spheres[i].vec3_cords);
		hit->vars_sp.a = 1.0;
		hit->vars_sp.b = 2.0 * dot_product(ray->ray_direction, origin);
		hit->vars_sp.c = dot_product(origin, origin) \
		- data->spheres[i].diameter * data->spheres[i].diameter / 4.0;
		hit->vars_sp.descriminent = square(hit->vars_sp.b) - \
		4.0 * hit->vars_sp.a * hit->vars_sp.c;
		if (hit->vars_sp.descriminent < 0)
			continue ;
		hit->vars_sp.t = (-hit->vars_sp.b - sqrt(hit->vars_sp.descriminent)) \
		/ (2.0 * hit->vars_sp.a);
		if (hit->vars_sp.t > 0.0 && hit->vars_sp.t < hit->hit_distance)
		{
			setter(hit, data, i);
		}
	}
}
