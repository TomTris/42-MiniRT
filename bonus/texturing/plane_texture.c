/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:05:05 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

typedef struct s_many_vars
{
	t_vec3	vector1;
	t_vec3	vector2;
	t_vec3	vector3;
	double	ax;
	double	bx;
	double	ay;
	double	by;
	double	cx;
	double	cy;
	int		seen;
}	t_many_vars;

t_vec3	get_vec3(t_hit *hit)
{
	double	d;

	d = dot_product(hit->cords, hit->normal);
	if (hit->normal.x == 0)
		return (create_vec3(1, 0, 0));
	if (hit->normal.y == 0)
		return (create_vec3(0, 1, 0));
	if (hit->normal.z == 0)
		return (create_vec3(0, 0, 1));
	if (d == 0)
		return (subtract(hit->cords, create_vec3(-(hit->normal.y / \
		hit->normal.x), 1, 0)));
	return (subtract(hit->cords, create_vec3(d, 0, 0)));
}

void	fill_vars(t_many_vars *vars)
{
	if (vars->vector1.x != 0 || vars->vector2.x != 0)
	{
		vars->ax = vars->vector1.x;
		vars->bx = vars->vector2.x;
		vars->cx = vars->vector3.x;
		vars->seen = 1;
	}
	if (vars->vector1.y != 0 || vars->vector2.y != 0)
	{
		if (vars->seen == 1)
		{
			vars->ay = vars->vector1.y;
			vars->by = vars->vector2.y;
			vars->cy = vars->vector3.y;
		}
		else
		{
			vars->ax = vars->vector1.y;
			vars->bx = vars->vector2.y;
			vars->cx = vars->vector3.y;
		}
		vars->seen++;
	}
}

void	calculate_uv(t_many_vars *vars, double *u, double *v)
{
	if (vars->ax == 0 && vars->by == 0)
	{
		*v = vars->cx / vars->bx;
		*u = vars->cy / vars->ay;
	}
	else if (vars->ax == 0)
	{
		*v = vars->cx / vars->bx;
		*u = (vars->cy - *v * vars->by) / vars->ay;
	}
	else if (vars->by == 0)
	{
		*u = vars->cy / vars->ay;
		*v = (vars->cx - *u * vars->ax) / vars->bx;
	}
	else
	{
		*v = (vars->cy - vars->cx * vars->ay) / (vars->by * \
		vars->ax - vars->bx * vars->ay);
		*u = (vars->cx - *v * vars->bx) / vars->ax;
	}
}

void	get_uv_plane(t_hit *hit, double *u, double *v)
{
	t_many_vars	vars;

	vars.vector3 = subtract(hit->world_position, hit->cords);
	if (dot_product(vars.vector3, vars.vector3) < 10e-9)
	{
		*u = 0;
		*v = 0;
		return ;
	}
	vars.vector1 = normalize(get_vec3(hit));
	vars.vector2 = normalize(cross(vars.vector1, hit->normal));
	vars.seen = 0;
	fill_vars(&vars);
	if (vars.seen == 1 && (vars.vector1.z != 0 || vars.vector2.z != 0))
	{
		vars.ay = vars.vector1.z;
		vars.by = vars.vector2.z;
		vars.cy = vars.vector3.z;
		vars.seen++;
	}
	calculate_uv(&vars, u, v);
}

t_vec3	apply_texture_plane(t_hit *hit)
{
	double	u;
	double	v;
	t_vec3	res;
	int		pixel_x;
	int		pixel_y;

	get_uv_plane(hit, &u, &v);
	u -= floor(u);
	v -= floor(v);
	pixel_x = (int)(u * (hit->texture->width - 1) + 0.5);
	pixel_y = (int)(v * (hit->texture->height - 1) + 0.5);
	modify_values(hit->texture, &pixel_x, &pixel_y);
	res.x = (double)hit->texture->pixels[(pixel_y * hit->texture->width \
	+ pixel_x) * 4] / 255.0;
	res.y = (double)hit->texture->pixels[(pixel_y * hit->texture->width \
	+ pixel_x) * 4 + 1] / 255.0;
	res.z = (double)hit->texture->pixels[(pixel_y * hit->texture->width \
	+ pixel_x) * 4 + 2] / 255.0;
	return (res);
}
