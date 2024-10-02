/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:07:06 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_vec3	checker_plane(t_hit *hit)
{
	double	u;
	double	v;

	get_uv_plane(hit, &u, &v);
	if (((long long)floor(u / pow(hit->plane->dist, 0.75)) + \
	(long long)floor(v / pow(hit->plane->dist, 0.75))) % 2 == 0)
		return (create_vec3(1, 1, 1));
	return (hit->color);
}

t_vec3	checker_sphere(t_hit *hit)
{
	double	theta;
	double	phi;
	int		lat_band;
	int		lon_band;

	theta = atan2(hit->world_normal.y, hit->world_normal.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	phi = acos(hit->world_normal.z);
	phi = pow(phi, 0.7);
	lat_band = (int)(phi / M_PI * 30);
	lon_band = (int)(theta / (2.0 * M_PI) * 20);
	if ((lat_band + lon_band) % 2 == 0)
		return (create_vec3(1, 1, 1));
	else
		return (hit->color);
}

t_vec3	stripe_at_object(t_hit *hit)
{
	if (hit->type == 2)
	{
		return (checker_plane(hit));
	}
	if (hit->type == 1)
	{
		return (checker_sphere(hit));
	}
	if (hit->type == 3)
	{
		return (apply_texture_cylinder(hit));
	}
	return (hit->color);
}

t_vec3	manage_textures(t_hit *hit)
{
	if (hit->type == 1)
		return (apply_texture_sphere(hit));
	if (hit->type == 2)
		return (apply_texture_plane(hit));
	if (hit->type == 3)
		return (apply_texture_cylinder(hit));
	return (hit->color);
}

t_vec3	get_color(t_hit *hit)
{
	t_vec3	color;

	color = hit->color;
	if (hit->checkers)
		color = stripe_at_object(hit);
	else if (hit->texture)
		color = manage_textures(hit);
	return (color);
}
