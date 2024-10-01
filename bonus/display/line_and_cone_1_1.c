/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_1_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/09/30 20:09:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_point_x_nor_vec	line_x_cone(t_line *line, t_cone *cone)
{
	t_point_x_nor_vec	ret;

	ret = line_x_cone_bottom(line, cone);
	if (ret.amount == 1)
		return (ret);
	return (line_x_cone_surface(line, cone));
}
