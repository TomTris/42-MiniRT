/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_point_x_nor_vec	cone_texture_bottom(t_point_x_nor_vec *ret, t_cone *cone)
{
	double	temp;
	int		height;
	int		width;
	t_vec3	ox;

	ox = vector_p1_to_p2(cone->po, ret->p);
	temp = vector_length(ox) * cos_alpha_2_vector(&cone->bottom_ori_vec, &ox);
	height = (int)(((temp + cone->r) / cone->diameter) * cone->texture->height);
	temp = vector_length(ox) * cos_alpha_2_vector(&cone->bottom_ori_vec2, &ox);
	width = (int)(((temp + cone->r) / cone->diameter) * cone->texture->width);
	ret->color.x = \
		(double)cone->texture->pixels[((height \
		* cone->texture->width + width) * 4)] / 255.0;
	ret->color.y = \
		(double)cone->texture->pixels[((height * \
		cone->texture->width + width) * 4 + 1)] / 255.0;
	ret->color.z = \
		(double)cone->texture->pixels[((height * \
		cone->texture->width + width) * 4 + 2)] / 255.0;
	return (*ret);
}

void	cone_checker_bottom(t_point_x_nor_vec *ret, t_cone *cone)
{
	double	dis;
	double	width;
	int		color;
	t_vec3	ox;
	double	alpha;

	color = 1;
	dis = cal_distance(cone->po, ret->p);
	width = cone->r / 6;
	if ((int)(dis / width) % 2 == 1)
		color *= -1;
	ox = vector_p1_to_p2(cone->po, ret->p);
	alpha = alpha_2_vector(&ox, &cone->bottom_ori_vec);
	if ((int)((alpha + cone->bottom_angle_2) / cone->bottom_angle) % 2 == 1)
		color *= -1;
	if (color == 1)
		ret->color = cone->vec3_color;
	else
		ret->color = create_vec3(1, 1, 1);
}

t_point_x_nor_vec	line_x_cone(t_line *line, t_cone *cone)
{
	t_point_x_nor_vec	ret;

	ret.color = create_vec3(0, 255, 255);
	ret = line_x_cone_bottom(line, cone);
	if (ret.amount == 1)
	{
		if (cone->texture != NULL)
			return (cone_texture_bottom(&ret, cone));
		if (cone->checkers == 0)
		{
			ret.color = cone->vec3_color;
			return (ret);
		}
		cone_checker_bottom(&ret, cone);
		return (ret);
	}
	return (line_x_cone_surface(line, cone));
}
