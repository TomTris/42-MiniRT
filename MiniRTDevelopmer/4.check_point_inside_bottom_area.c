/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.check_point_inside_bottom_area.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:09:46 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 22:51:23 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

int is_point_inside_bottom_area(t_point pA, t_point pO, t_vec3 vAO, double r)
{
	t_plain	plain;
	double	distance;

	plain = plain_of_bottom_area(pO, vAO);
	distance = sqrt((pA.x - pO.x) * (pA.x - pO.x) \
					+ (pA.y - pO.y) * (pA.y - pO.y) \
					+ (pA.z - pO.z) * (pA.z - pO.z));
	if (distance < r)
		return (1);
	return (0);
}
