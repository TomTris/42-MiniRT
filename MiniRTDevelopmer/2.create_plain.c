/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.create_plain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:07:07 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 22:52:43 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

t_plain plain_from_3_points(t_point p1, t_point p2, t_point p3)
{
	t_plain plain;

	plain.a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
	plain.b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z);
	plain.c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	plain.d = -(plain.a * p1.x + plain.b * p1.y + plain.c * p1.z);
	return (plain);
}

t_plain plain_of_bottom_area(t_point pO, t_vec3 vAO)
{
	t_plain	plain;

	plain.a = vAO.x;
	plain.b = vAO.y;
	plain.c = vAO.z;
	plain.d = - (plain.a * pO.x + plain.b * pO.y + plain.c * pO.y);
	return (plain);
}
