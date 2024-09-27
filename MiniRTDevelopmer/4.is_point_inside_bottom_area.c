/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.is_point_inside_bottom_area.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:09:46 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 23:55:10 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

//Use only now point is in the same plain of bottom area
int is_point_inside_bottom_area(t_cone co, t_point p)
{
	if (co.r >= sqrt(pow(co.pO.x - p.x, 2) \
				+ pow(co.pO.y - p.y, 2) \
				+ pow(co.pO.z - p.z, 2)))
		return (1);
	return (0);
}
