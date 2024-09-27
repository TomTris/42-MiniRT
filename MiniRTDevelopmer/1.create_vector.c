/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.other_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:23:41 by qdo               #+#    #+#             */
/*   Updated: 2024/09/28 00:36:43 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

t_vec3	vector_cross_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_vec3	vector_AO_form_A_O(t_point pA, t_point pO)
{
	t_vec3	ret;

	ret.x = pO.x - pA.x;
	ret.y = pO.y - pA.y;
	ret.z = pO.z - pA.z;
	return (ret);
}
