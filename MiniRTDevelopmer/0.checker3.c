/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.checker3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:58:23 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 00:33:46 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

int is_on_plain(t_plain pl, t_point p)
{
	if (pl.a * p.x + pl.b * p.y + pl.c + p.z + pl.d == 0)
		return (1);
	return (0);
}

int	is_valid_cone(t_cone cone)
{
	t_vec3	vAO;

	vAO = vector_AO_form_A_O(cone.pA, cone.pO);
	if (is_valid_vector(cone.vAO) && is_valid_vector(vAO) && cone.r > 0 \
		&& is_two_vector_same_direction(cone.vAO, vAO))
		return (1);
	return (0);
}
