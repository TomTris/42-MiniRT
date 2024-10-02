/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_planes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:43:46 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	set_type_distance_pl(t_hit *hit, t_data *data, int i)
{
	hit->hit_distance = hit->vars_sp.t;
	hit->found = 1;
	hit->type = 2;
	hit->color = data->planes[i].vec3_color;
	hit->cords = data->planes[i].vec3_cords;
	hit->normal = data->planes[i].vec3_norm;
	hit->plane = &data->planes[i];
	hit->checkers = data->planes[i].checkers;
	hit->texture = data->planes[i].texture;
}

double	get_factor(t_vec3 *norm, t_vec3	*point, t_vec3 *camera)
{
	t_var_sphere	vars;

	vars.d = dot_product(*norm, *point);
	vars.a = dot_product(*camera, *norm);
	vars.b = dot_product(*norm, *norm);
	vars.c = vars.d - vars.a;
	vars.t = vars.c / vars.b;
	if (vars.t < 0)
		return (1.0);
	return (-1.0);
}

void	handle_planes(t_data *data, t_ray *ray, t_hit *hit)
{
	int	i;

	i = -1;
	while (++i < data->amount_of_planes)
	{
		hit->vars_sp.d = \
dot_product(data->planes[i].vec3_cords, data->planes[i].vec3_norm);
		hit->vars_sp.a = \
dot_product(ray->ray_origin, data->planes[i].vec3_norm);
		hit->vars_sp.b = \
dot_product(ray->ray_direction, data->planes[i].vec3_norm);
		hit->vars_sp.c = hit->vars_sp.d - hit->vars_sp.a;
		if (hit->vars_sp.b == 0)
			continue ;
		hit->vars_sp.t = hit->vars_sp.c / hit->vars_sp.b;
		if (hit->vars_sp.t > 0.0 && hit->vars_sp.t < hit->hit_distance)
		{
			set_type_distance_pl(hit, data, i);
		}
	}
}
