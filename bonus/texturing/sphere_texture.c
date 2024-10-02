/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:14:19 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

typedef struct s_uv
{
	double	u;
	double	v;
}	t_uv;

void	modify_values(mlx_texture_t *texture, int *pixel_x, int *pixel_y)
{
	if (*pixel_x < 0)
		*pixel_x = 0;
	if (*pixel_x >= (int)texture->width)
		*pixel_x = texture->width - 1;
	if (*pixel_y < 0)
		*pixel_y = 0;
	if (*pixel_y >= (int)texture->height)
		*pixel_y = texture->height - 1;
}

t_vec3	apply_texture_sphere(t_hit *hit)
{
	t_vec3			vec;
	mlx_texture_t	*texture;
	t_uv			uv;
	int				pixel_x;
	int				pixel_y;

	texture = hit->texture;
	uv.u = (atan2(-hit->world_normal.z, -hit->world_normal.x)) \
	/ (2 * M_PI) + 0.5;
	uv.v = asin(-hit->world_normal.y) / M_PI + 0.5;
	pixel_x = (int)(uv.u * (texture->width - 1) + 0.5);
	pixel_y = (int)(uv.v * (texture->height - 1) + 0.5);
	vec.x = (double)texture->pixels[(pixel_y * \
	texture->width + pixel_x) * 4] / 255.0;
	vec.y = (double)texture->pixels[(pixel_y * \
	texture->width + pixel_x) * 4 + 1] / 255.0;
	vec.z = (double)texture->pixels[(pixel_y * \
	texture->width + pixel_x) * 4 + 2] / 255.0;
	return (vec);
}
