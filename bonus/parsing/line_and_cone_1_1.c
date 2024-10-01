/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_1_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/10/01 17:49:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double alpha_2_vector(t_vec3 *v1, t_vec3 *v2)
{
	double top;
	double down;

	top = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	down = sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) \
		* sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
	return (acos(top / down));
}

void	color_decide1(t_point_x_nor_vec *ret, t_cone *cone)
{
	double	dis;
	double	width;
	int		color;
	t_vec3	ox;
	double alpha;

	if (cone->checkers == 0)
	{
		ret->color = cone->vec3_color;
		return ;
	}
	color = 1;
	dis = cal_distance(cone->po, ret->p);
	width = cone->r / 6;
	if ((int) (dis / width) % 2 == 1)
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

	ret.color = create_vec3(0,255, 255);
	ret = line_x_cone_bottom(line, cone);
	if (ret.amount == 1)
	{
		color_decide1(&ret, cone);
		return (ret);
	}
	return (line_x_cone_surface(line, cone));
}
