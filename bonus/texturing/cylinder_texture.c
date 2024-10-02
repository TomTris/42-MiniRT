/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:07 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 15:04:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


t_vec3	find_point_in_bottom_cylinder(t_vec3 *p, t_plain *pl, t_vec3 *norm)
{
	double	t;
	t_vec3	vap;

	t = -(pl->a * p->x + pl->b * p->y + pl->c * p->z + pl->d) / \
		(pl->a * norm->x + pl->b * norm->y + pl->c * norm->z);
	vap.x = p->x + norm->x * t;
	vap.y = p->y + norm->y * t;
	vap.z = p->z + norm->z * t;
	return (vap);	
}

t_abc	cal_abc_cy(t_line *li, double r)
{
	t_abc	abc;

	abc.a = pow(li->dv.x, 2) + pow(li->dv.y, 2) + pow(li->dv.z, 2);
	abc.b = 0;
	abc.c = - pow(r, 2);
	return (abc);
}

void	cylinder_x_plain(t_cylinder *cy, t_vec3 *vab)
{
	t_line	li;
	t_abc abc;
	double delta;
	double t;
	t_vec3	intersec;
	
	if (vab->x == 0.0)
		li.dv = create_vec3(1,0,0);	
	else if (vab->y == 0.0)
		li.dv = create_vec3(0,1,0);	
	else if (vab->z == 0.0)
		li.dv = create_vec3(0,0,1);	
	else
		li.dv = vector_cross_product(*vab, create_vec3(1, 0 ,0));
	abc = cal_abc_cy(&li, cy->r);
	delta = sqrt(pow(abc.b, 2) - 4 * abc.a * abc.c);
	t = (-abc.b - delta) / (2 * abc.a);
	intersec.x = cy->pa.x + li.dv.x * t;
	intersec.y = cy->pa.y + li.dv.y * t;
	intersec.z = cy->pa.z + li.dv.z * t;
	cy->bottom_ori_vec = vector_p1_to_p2(cy->pa, intersec);
	cy->bottom_ori_vec2 = vector_cross_product(cy->vab, cy->bottom_ori_vec);
}

double	distance_p_pl(t_vec3 *p, t_plain *pl)
{
	double ret;
	
	ret = (pl->a * p->x + pl->b * p->y + pl->c * p->z + pl->d) / \
		(sqrt(pow(pl->a, 2) + pow(pl->b, 2) + pow(pl->c, 2)));
	if (ret <0)
		ret *= -1;
	return (ret);
}

t_vec3	cy_x_checker_bottom(t_cylinder *cy, t_vec3 *p, int type)
{
	double	temp;
	t_vec3	ox;
	int	color;

	color = 1;
	if (type == 2)
		ox = vector_p1_to_p2(cy->pa, *p);
	else
		ox = vector_p1_to_p2(cy->pb, *p);
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec, &ox);
	if ((int)((temp + cy->r) / cy->diameter * 10) % 2 == 0)
		color = -1;
	temp = vector_length(ox) * cos_alpha_2_vector(&cy->bottom_ori_vec2, &ox);
	if ((int)((temp + cy->r) / cy->diameter * 10) % 2 == 0)
		color *= -1;
	if (color == 1)
		return (create_vec3(1,1,1));
	return (cy->vec3_color);
}

t_vec3	cy_x_checker_side(t_cylinder *cy, t_vec3 *p)
{
	int	color;
	color = 1;

	double	height = distance_p_pl(p, &cy->pl_top);
	if ((int)(height * 10 / cy->height) % 2 == 0)
		color = -1;
	t_vec3	o2 = add(cy->pa, scale(cy->vab, height / cy->height));
	t_vec3	o2p = vector_p1_to_p2(o2, *p);
	double	alpha = alpha_2_vector(&cy->bottom_ori_vec, &o2p);
	if ((int)(alpha / cy->alpha_divided + 0.5) % 2 == 0)
		color *= -1;
	if (color == 1)
		return (create_vec3(1, 1, 1));
	return (cy->vec3_color);
}

t_vec3	cy_x_texture_bottom(t_cylinder *cy, t_vec3 *p, int type)
{
	double	temp;
	int	height;
	int	width;
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

t_vec3	cy_x_texture_side(t_cylinder *cy, t_vec3 *p)
{
	int		height;
	double		temp;
	t_vec3	o2;
	t_vec3	o2p;
	double	alpha;
	t_vec3	ret;
	int width;

	temp = distance_p_pl(p, &cy->pl_top);
	o2 = add(cy->pa, scale(cy->vab, -temp));
	height = (int)(temp / cy->height * cy->texture->height);
	o2p = vector_p1_to_p2(o2, *p);
	alpha = alpha_2_vector(&cy->bottom_ori_vec, &o2p);
	if (value_a_vector(vector_cross_product(cy->bottom_ori_vec, o2p)) < 0)
		alpha = 2 * M_PI - alpha;
	alpha /= (2 * M_PI);
	width = (int)(alpha * cy->texture->width);
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

// type_cy == 1 side  type_cy == 2 bottom  3 top
// hit->type_cy == 1;
// hit->world_position = p;

t_vec3	apply_texture_cylinder(t_hit *hit)
{
	t_cylinder *cy = hit->cylinder;
	t_vec3		p;

	p = hit->world_position;
	cy->vab = cy->vec3_norm;
	cylinder_x_plain(cy, &cy->vab);
	cy->r = cy->diameter / 2;
	cy->pa = add(cy->vec3_cords, scale(cy->vab, cy->height / 2.0));
	cy->pl_top.a = cy->vab.x;
	cy->pl_top.b = cy->vab.y;
	cy->pl_top.c = cy->vab.z;
	cy->pl_top.d = -(cy->vab.x * cy->pa.x + cy->vab.y * cy->pa.y + cy->vab.z * cy->pa.z);
	cy->pb = add(cy->vec3_cords, scale(cy->vab, cy->height / -2.0));
	cy->pl_bot.a = cy->vab.x;
	cy->pl_bot.b = cy->vab.y;
	cy->pl_bot.c = cy->vab.z;
	cy->pl_bot.d = -(cy->vab.x * cy->pb.x + cy->vab.y * cy->pb.y + cy->vab.z * cy->pb.z);
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
