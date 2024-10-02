/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_x_cone_2_2_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:41:07 by qdo               #+#    #+#             */
/*   Updated: 2024/10/02 18:46:43 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_point_nvec	cone_and_texture2(t_point_nvec *ret, t_cone *cone)
{
	int		height;
	t_vec3	point_in_bottom;
	double	alpha;
	t_vec3	ox;
	int		width;

	height = ((cal_distance(cone->pa, ret->p)) / cone->s) \
			* cone->texture->height;
	point_in_bottom = find_point_in_bottom(&ret->p, &cone->pl, &cone->pa);
	ox = vector_p1_to_p2(cone->po, point_in_bottom);
	alpha = alpha_2_vector(&ox, &cone->bottom_ori_vec);
	if (value_a_vector(vector_cross_product(cone->bottom_ori_vec, ox)) < 0)
		alpha = 2 * M_PI - alpha;
	alpha /= (2 * M_PI);
	width = (int)(alpha * cone->texture->width);
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

t_point_nvec	color_decide2(t_point_nvec *ret, t_cone *cone)
{
	int		color;
	t_vec3	point_in_bottom;
	double	alpha;
	t_vec3	ox;

	if (cone->texture != 0)
		return (cone_and_texture2(ret, cone));
	if (cone->checkers == 0)
		return (ret->color = cone->vec3_color, *ret);
	color = 1;
	if ((int)(cal_distance(cone->pa, ret->p) / cone->surface_width) % 2 == 1)
		color *= -1;
	point_in_bottom = find_point_in_bottom(&ret->p, &cone->pl, &cone->pa);
	ox = vector_p1_to_p2(cone->po, point_in_bottom);
	alpha = alpha_2_vector(&ox, &cone->bottom_ori_vec);
	if ((int)((alpha + cone->bottom_angle_2) / cone->bottom_angle) % 2 == 1)
		color *= -1;
	if (color == 1)
		ret->color = cone->vec3_color;
	else
		ret->color = create_vec3(1, 1, 1);
	return (*ret);
}
