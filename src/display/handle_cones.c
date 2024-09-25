/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cones.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:34:18 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/25 20:03:41 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

typedef struct s_vars
{
	t_vec3	point_line;	
	t_vec3	dir_line;
	t_vec3	apex;
	t_vec3	normal;

	double	diameter;
	double	height;
}	t_vars;


void	handle_cones(t_data *data, t_ray *ray, t_hit *hit)
{
	int		i;
	t_vars	vars;
	// double	t;

	i = -1;
	vars.point_line = ray->ray_origin;
	vars.dir_line = ray->ray_direction;
	while (++i < data->amount_of_cones)
	{
		vars.apex = data->cones[i].vec3_cords;
		vars.normal = data->cones[i].vec3_norm;
		vars.diameter = data->cones[i].diameter;
		vars.height = data->cones[i].height;
		if (hit->vars_sp.t > 0)
		{
			hit->hit_distance = hit->vars_sp.t;
			hit->found = 1;
			hit->type = 4;
			hit->color = data->cones[i].vec3_color;
			hit->cords = data->cones[i].vec3_cords;
			hit->normal = data->cones[i].vec3_norm;
		}
	}
}