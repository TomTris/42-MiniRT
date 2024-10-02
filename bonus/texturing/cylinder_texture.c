/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:07 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_vec3	cy_x_checker_side(t_cylinder *cy, t_vec3 *p)
{
	int		color;
	double	height;
	t_vec3	o2;
	t_vec3	o2p;
	double	alpha;

	color = 1;
	height = distance_p_pl(p, &cy->pl_top);
	if ((int)(height * 8 / cy->height) % 2 == 0)
		color = -1;
	o2 = add(cy->pa, scale(cy->vab, -height));
	o2p = vector_p1_to_p2(o2, *p);
	alpha = alpha_2_vector(&cy->bottom_ori_vec, &o2p);
	if (value_a_vector(vector_cross_product(cy->bottom_ori_vec, o2p)) < 0)
		alpha = 2 * M_PI - alpha;
	if ((int)(alpha / (2 * M_PI / 8)) % 2 == 0)
		color *= -1;
	if (color == 1)
		return (create_vec3(1, 1, 1));
	return (cy->vec3_color);
}

t_vec3	cy_x_texture_bottom(t_cylinder *cy, t_vec3 *p, int type)
{
	double	temp;
	int		height;
	int		width;
	t_vec3	ox;
	t_vec3	ret;

	if (type == 2)
		ox = vector_p1_to_p2(cy->pa, *p);
	else
		ox = vector_p1_to_p2(cy->pb, *p);
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec, &ox);
	height = (int)(((temp + cy->r) / cy->diameter) * cy->texture->height);
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec2, &ox);
	width = (int)(((temp + cy->r) / cy->diameter) * cy->texture->width);
	ret.x = \
		(double)cy->texture->pixels[((height \
		* cy->texture->width + width) * 4)] / 255.0;
	ret.y = \
		(double)cy->texture->pixels[((height * \
		cy->texture->width + width) * 4 + 1)] / 255.0;
	ret.z = \
		(double)cy->texture->pixels[((height * \
		cy->texture->width + width) * 4 + 2)] / 255.0;
	return (ret);
}

typedef struct s_val_holder {
	int		height;
	double	temp;
	t_vec3	o2;
	t_vec3	o2p;
	double	alpha;
	t_vec3	ret;
	int		width;
}	t_val_holder;

t_vec3	cy_x_texture_side(t_cylinder *cy, t_vec3 *p)
{
	t_val_holder	t;

	t.temp = distance_p_pl(p, &cy->pl_top);
	t.o2 = add(cy->pa, scale(cy->vab, -t.temp));
	t.height = (int)(t.temp / cy->height * cy->texture->height);
	t.o2p = vector_p1_to_p2(t.o2, *p);
	t.alpha = alpha_2_vector(&cy->bottom_ori_vec, &t.o2p);
	if (value_a_vector(vector_cross_product(cy->bottom_ori_vec, t.o2p)) < 0)
		t.alpha = 2 * M_PI - t.alpha;
	t.alpha /= (2 * M_PI);
	t.width = (int)(t.alpha * cy->texture->width);
	t.ret.x = \
		(double)cy->texture->pixels[((t.height \
		* cy->texture->width + t.width) * 4)] / 255.0;
	t.ret.y = \
		(double)cy->texture->pixels[((t.height * \
		cy->texture->width + t.width) * 4 + 1)] / 255.0;
	t.ret.z = \
		(double)cy->texture->pixels[((t.height * \
		cy->texture->width + t.width) * 4 + 2)] / 255.0;
	return (t.ret);
}

t_vec3	apply_texture_cylinder2(t_cylinder *cy, t_vec3 p, t_hit *hit)
{
	if (cy->texture != NULL)
	{
		if (hit->type_cy == 1)
			return (cy_x_texture_side(cy, &p));
		return (cy_x_texture_bottom(cy, &p, hit->type_cy));
	}
	if (cy->checkers == 1)
	{
		if (hit->type_cy != 1)
			return (cy_x_checker_bottom(cy, &p, hit->type_cy));
		return (cy_x_checker_side(cy, &p));
	}
	return (cy->vec3_color);
}

t_vec3	apply_texture_cylinder(t_hit *hit)
{
	t_cylinder	*cy;
	t_vec3		p;

	cy = hit->cylinder;
	p = hit->world_position;
	cy->vab = cy->vec3_norm;
	cylinder_x_plain(cy, &cy->vab);
	cy->r = cy->diameter / 2;
	cy->pa = add(cy->vec3_cords, scale(cy->vab, cy->height / 2.0));
	cy->pl_top.a = cy->vab.x;
	cy->pl_top.b = cy->vab.y;
	cy->pl_top.c = cy->vab.z;
	cy->pl_top.d = -(cy->vab.x * cy->pa.x + \
		cy->vab.y * cy->pa.y + \
		cy->vab.z * cy->pa.z);
	return (apply_texture_cylinder2(cy, p, hit));
}
